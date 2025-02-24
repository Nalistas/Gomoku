/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MonteCarlo
*/

#include "Board.hpp"
#include "Matrix.hpp"
#include "Thread/ThreadPool.hpp"

#ifndef MONTECARLO_HPP_
    #define MONTECARLO_HPP_

class MonteCarlo {
    public:
        MonteCarlo(Board const &board, thread::ThreadPool<std::function<Matrix(void)>, Matrix> &pool);
        ~MonteCarlo();

        std::pair<int, int> computePlay(void);
        Matrix computeSingleGame(void) const;
        Matrix evaluateBoard(Board const &board) const;
    protected:
        Board const &_board;
        thread::ThreadPool<std::function<Matrix(void)>, Matrix> &_pool;
};

#endif /* !MONTECARLO_HPP_ */
