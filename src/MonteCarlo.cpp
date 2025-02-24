/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MonteCarlo
*/

#include "MonteCarlo.hpp"
#include "Board.hpp"
#include <iostream>
#include <list>
#include "Thread/Promise.hpp"

MonteCarlo::MonteCarlo(Board const &board, thread::ThreadPool<std::function<Matrix(void)>, Matrix> &pool) :
    _board(board), _pool(pool)
{}

MonteCarlo::~MonteCarlo()
{}

std::pair<int, int> MonteCarlo::computePlay(void)
{
    Matrix final_matrix(this->_board.get_x(), this->_board.get_y());
    std::list<thread::Promise<Matrix>> promesses;

    for (int i = 0; i < 50000; i++) {
        auto task = std::function<Matrix()>([this]() { return this->computeSingleGame(); });
        promesses.emplace_back(this->_pool.addTask(task));
    }
    for (auto &promise : promesses) {
        final_matrix += promise.get();
    }
    int x_max = 0;
    int y_max = 0;
    double val_max = 0;
    int m_cols = final_matrix.cols();
    int m_rows = final_matrix.rows();
    for (int i = 0; i < m_cols; i++) {
        for(int j = 0; j < m_rows; j++) {
            if (final_matrix(i, j) > val_max && this->_board.get_cell(i, j) == Cell::Empty) {
                x_max = i;
                y_max = j;
                val_max = final_matrix(i, j);
            }
        }
    }
    return std::make_pair(x_max, y_max);
}

Matrix MonteCarlo::computeSingleGame(void) const
{
    Board copy = this->_board;

    for (int i = 0; i < 30 && copy.get_plays().empty() == false; ++i) {
        std::pair<int, int> const &random_play = copy.get_random_empty_case();
        copy.trace_play(random_play.first, random_play.second, (i % 2 == 0) ? Cell::Me : Cell::Opponent);
    }
    return this->evaluateBoard(copy);
}

Matrix MonteCarlo::evaluateBoard(Board const &copy) const
{
    std::list<std::vector<std::pair<int, int>>> combinaisons = copy.get_all_combinaisons();
    Matrix matrix(this->_board.get_x(), this->_board.get_y());

    for (const auto &combinaison : combinaisons) {
        bool estAllie = (copy.get_cell(combinaison[0].first, combinaison[0].second) == Cell::Me);

        double poids = 0.0;
        int taille = combinaison.size();
        if (taille >= 5) poids = estAllie ? 1.0 : 2.0;
        else if (taille == 4) poids = estAllie ? 0.1 : 0.2;
        else if (taille == 3) poids = estAllie ? 0.005 : 0.01;

        for (const auto &cell : combinaison) {
            int x = cell.first;
            int y = cell.second;
            matrix(x, y) += poids;
        }
    }

    return matrix;
}

// function MCTS(root_state):
//     root_node = create_node(root_state)

//     while within time/budget:
//         node = Selection(root_node)
//         if not terminal(node.state):
//             child_node = Expansion(node)
//         result = Simulation(child_node, max_depth=15)  # Simulation limitée à 15 coups
//         Backpropagation(child_node, result)

//     return best_move(root_node)

// function Selection(node):
//     while node is fully expanded and not terminal(node.state):
//         node = best_child(node)
//     return node

// function Expansion(node):
//     if not fully_expanded(node):
//         return expand_child(node)
//     return node  # Si pas d'expansion possible, retourne le même nœud

// function Simulation(node, max_depth):
//     current_state = copy(node.state)
//     depth = 0
//     while not terminal(current_state) and depth < max_depth:
//         current_state = random_move(current_state)
//         depth += 1
//     return evaluate_partial_state(current_state)  # Retourne une évaluation non finale

// function Backpropagation(node, result):
//     while node is not null:
//         node.visits += 1
//         node.wins += result  # Resultat basé sur l'évaluation partielle
//         node = node.parent

// function best_child(node):
//     best_score = -∞
//     best_node = null
//     for child in node.children:
//         score = UCT(child)
//         if score > best_score:
//             best_score = score
//             best_node = child
//     return best_node

// function UCT(node):
//     exploitation = node.wins / node.visits
//     exploration = sqrt(2 * log(node.parent.visits) / node.visits)
//     return exploitation + exploration

// function evaluate_partial_state(state):
//     score = 0
//     for each line (row, column, diagonal) in state:
//         if player has 4 in a row and it's unblocked:
//             score += 100  # Presque une victoire
//         if player has 3 in a row and it's unblocked:
//             score += 10   # Très bon coup
//         if player has 2 in a row:
//             score += 1    # Potentiellement utile plus tard
//         if opponent has 4 in a row:
//             score -= 100  # Très dangereux, à bloquer
//     return score
