/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Board
*/

#include "Board.hpp"
#include <list>
#include <stdexcept>
#include <iostream>
#include <array>
#include <set>

static const std::array<std::pair<int, int>, 8> directions = {
    std::make_pair(-1, -1), // Top-left
    std::make_pair(-1, 0),  // Top
    std::make_pair(-1, 1),  // Top-right
    std::make_pair(0, -1),  // Left

    /*
    ^ ^ ^
    ^   v
    v v v
    */

    std::make_pair(0, 1),   // Right
    std::make_pair(1, -1),  // Bottom-left
    std::make_pair(1, 0),   // Bottom
    std::make_pair(1, 1)    // Bottom-right
};

Board::Board()
{
    set_size(20, 20);
}

Board::~Board()
{}

Board::Board(int x, int y)
{
    set_size(x, y);
}

Board::Board(int side)
{
    set_size(side, side);
}

void Board::set_size(int x, int y)
{
    _x = x;
    _y = y;
    _board.resize(_x);
    for (int i = 0; i < _x; i++) {
        _board[i].resize(_y);
        for (int j = 0; j < _y; j++) {
            _board[i][j] = Cell::Empty;
            _plays.insert({i, j});
        }
    }
}

void Board::set_size(int side)
{
    set_size(side, side);
}

Cell Board::get_cell(int x, int y) const
{
    return (_board[x][y]);
}

Cell Board::get_winner() const
{
    const int directions[4][2] = {
        {1, 0},
        {0, 1},
        {1, 1},
        {1, -1}
    };

    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            if (_board[i][j] == Cell::Empty)
                continue;

            for (const auto& direction : directions) {
                int count = 1;
                int dx = direction[0], dy = direction[1];

                for (int step = 1; step < 5; step++) {
                    int nx = i + step * dx;
                    int ny = j + step * dy;

                    if (nx < 0 || nx >= _x || ny < 0 || ny >= _y)
                        break;

                    if (_board[nx][ny] == _board[i][j]) {
                        count++;
                    } else {
                        break;
                    }
                }

                if (count == 5) {
                    return _board[i][j];
                }
            }
        }
    }

    return Cell::Empty;
}


std::list<std::vector<std::pair<int, int>>> Board::get_all_combinaisons() const
{
    std::list<std::vector<std::pair<int, int>>> winners;
    std::array<std::array<int, 20>, 20> _tmp = {};

    const int directions[4][3] = {
        {1, 0},
        {0, 1},
        {1, 1},
        {1, -1}
    };

    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            if (_board[i][j] == Cell::Empty)
                continue;

            for (int dir = 1; dir < 5; dir++) {
                int dy = directions[dir - 1][1], dx = directions[dir - 1][0];
                int count = 1;

                if (_tmp[i][j] == dir || _tmp[i + dx][j + dy] == dir || i + 2 * dx >= _x || i + 2 * dx < 0 || j + 2 * dy >= _y || j + 2 * dy < 0) {
                    continue;
                }

                std::vector<std::pair<int, int>> winner = {{i, j}};

                for (int step = 1; true; step++) {
                    int nx = i + step * dx;
                    int ny = j + step * dy;

                    if (nx < 0 || nx >= _x || ny < 0 || ny >= _y || _board[nx][ny] != _board[i][j]) {
                        break;
                    }

                    _tmp[nx][ny] = dir;
                    winner.push_back({nx, ny});
                    count++;
                }

                if (count >= 3) {
                    winners.push_back(winner);
                }
            }
        }
    }

    return winners;
}

void Board::trace_play(int x, int y, Cell player) {
    if (x >= _x || y >= _y || x < 0 || y < 0)
        throw std::runtime_error("Invalid coordinates");

    if (_board[x][y] == Cell::Empty) {
        _board[x][y] = player;
        _plays.erase({x, y});
    } else {
        throw std::runtime_error("Case already played");
    }
}

int Board::get_x() const
{
    return this->_x;
}

int Board::get_y() const
{
    return this->_y;
}

std::ostream &operator<<(std::ostream &os, const Cell &state)
{
    switch (state) {
        case Cell::Empty:
            os << ".";
            break;
        case Cell::Me:
            os << "X";
            break;
        case Cell::Opponent:
            os << "O";
            break;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Cell &state)
{
    int int_state;

    is >> int_state;
    switch (int_state) {
    case 1:
        state = Cell::Me;
        break;
    case 2 :
        state = Cell::Opponent;
        break;
    default:
        break;
    }
    return is;
}

std::set<std::pair<int, int>> const &Board::get_plays() const
{
    return this->_plays;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    int x = board.get_x();
    int y = board.get_y();

    for (int i = 0; i < x; i++) {
        os << "|";
        for (int j = 0; j < y; j++) {
            os << board.get_cell(i, j);
        }
        os << "|";
        os << std::endl;
    }
    // for (auto it = board.get_plays().begin(); it != board.get_plays().end(); it++) {
    //     os << "{";
    //     os << it->first;
    //     os << " ";
    //     os << it->second;
    //     os << "}; ";
    // }
    os << std::endl;
    return os;
}

void Board::reset()
{
    _plays.clear();
    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            _board[i][j] = Cell::Empty;
            _plays.insert({i, j});
        }
    }
}

std::pair<int, int> const &Board::get_random_empty_case(void) const
{
    std::set<std::pair<int, int>> const &set_of_move = this->_plays;

    int randomIndex = std::rand() % set_of_move.size();
    auto it = set_of_move.begin();
    std::advance(it, randomIndex);
    return (*it);
}
