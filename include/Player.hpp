/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Player
*/

#include "Board.hpp"
#include "ManagerConnection.hpp"
#include "Thread/ThreadPool.hpp"
#include "Matrix.hpp"

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

class Player {
    public:
        Player(ManagerConnection &manager, Board &board);
        ~Player();
        void play(std::string const &command);
        void start(void);
        void set_board(void);

    private:
        void make_a_move(void);
        ManagerConnection &_manager;
        Board &_board;
        thread::ThreadPool<std::function<Matrix(void)>, Matrix> _pool;
};

#endif /* !PLAYER_HPP_ */
