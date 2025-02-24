/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Board
*/

#include <cstddef>
#include <vector>
#include <set>
#include <list>
#include <array>
#include <ostream>

#include "gomoku.hpp"

#ifndef BOARD_HPP_
    #define BOARD_HPP_

class Board {
    public:
        Board(int x, int y);
        Board(int side);
        Board();
        ~Board();

        void set_size(int side);
        void set_size(int x, int y);
        Cell get_cell(int x, int y) const;
        int get_x() const;
        int get_y() const;
        void reset();

        void trace_play(int x, int y, Cell player);
        std::set<std::pair<int, int>> const &get_plays() const;

        Cell get_winner() const;

        std::pair<int, int> const &get_random_empty_case(void) const;
        std::list<std::vector<std::pair<int, int>>> get_all_combinaisons() const;

    protected:

        int _x;
        int _y;
        std::vector<std::vector<Cell>> _board;
        std::set<std::pair<int, int>> _plays;
};

std::ostream &operator<<(std::ostream &os, const Board &board);
std::istream &operator>>(std::istream &is, Cell &state);

#endif /* !BOARD_HPP_ */
