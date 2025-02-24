/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Player
*/

#include "Player.hpp"
#include "ManagerConnection.hpp"
#include "MonteCarlo.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>

Player::Player(ManagerConnection &manager, Board &board) :
    _manager(manager), _board(board)
{
    char *rand_seed;
    std::uintptr_t address = reinterpret_cast<std::uintptr_t>(rand_seed);
    std::srand(static_cast<unsigned int>(address));

    manager.add_action("BEGIN", [this](std::string const &command) {this->start(); return 0;});
    manager.add_action("TURN", [this](std::string const &command) {this->play(command); return 0;});
    manager.add_action("BOARD", [this](std::string const &command) {this->set_board(); return 0;});
    manager.add_action("win", [&board, &manager](std::string const &command) {
        std::cout << std::to_string(static_cast<int>(board.get_winner())) << std::endl;
        return 0;
    });
    manager.add_action("print", [&board, &manager](std::string const &command) {
        std::cout << board << std::endl;
        return 0;
    });
    manager.add_action("RESTART", [&board, &manager](std::string const &command) {
        board.reset();
        manager.put("OK");
        return 0;
    });
    manager.add_action("START", [&board, &manager](std::string const &command) {
        int size = std::stoi(command);
        if (size < 5) {
            manager.put("ERROR: size must be at least 5");
        }
        board.set_size(size);
        manager.put("OK");
        return 0;
    });


    this->_pool.run();
}

Player::~Player()
{}

void Player::play(std::string const &command)
{
    size_t commaPos = command.find(',');
    std::string xStr = command.substr(0, commaPos);
    std::string yStr = command.substr(commaPos + 1);
    int x = std::stoi(xStr);
    int y = std::stoi(yStr);
    _board.trace_play(x, y, Cell::Opponent);
    this->make_a_move();
}

void Player::make_a_move(void)
{
    MonteCarlo monteCarlo(this->_board, this->_pool);
    std::pair<int, int> const &play = monteCarlo.computePlay();
    int x = play.first;
    int y = play.second;

    _manager.put(std::to_string(x) + "," + std::to_string(y));
    _board.trace_play(x, y, Cell::Me);
}

void Player::start()
{
    int x = _board.get_x() / 2;
    int y = _board.get_y() / 2;
    _manager.put(std::to_string(x) + "," + std::to_string(y));
    _board.trace_play(x, y, Cell::Me);
}

void Player::set_board()
{
    std::string line;
    int x;
    int y;
    Cell player;

    line = this->_manager.get();
    while (line.substr(0, 4) != "DONE" && line != "END") {
        std::istringstream ss(line);
        std::string x_str, y_str, player_str;

        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');
        std::getline(ss, player_str, ',');

        x = std::stoi(x_str);
        y = std::stoi(y_str);
        player = static_cast<Cell>(std::stoi(player_str));

        this->_board.trace_play(x, y, player);
        line = this->_manager.get();
    }
    this->make_a_move();
}


