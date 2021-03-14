#ifndef GAME_HEX_STATE_H_
#define GAME_HEX_STATE_H_

#include <iostream>
#include <stdexcept>
#include "hex_board.hpp"
#include "state.hpp"


template<>
Result game::State<game::HexBoard>::result() const {
    // perform dfs to check if the current Piece won
    auto board = get_board();
    auto n = board.get_board_size();
    auto curr_piece = board.get_piece(curr_move);

    bool topdown = curr_piece == Piece::White;
    bool first = false, second = false;
    std::vector<Point> v{curr_move};
    board.reset(curr_move);
    while (!v.empty()) {
        auto p = v.back();
        v.pop_back();
        if (topdown) {
            if (p.first == 0)
                first = true;
            else if (p.first == n-1)
                second = true;
        }
        else {
            if (p.second == 0)
                first = true;
            else if (p.second == n-1)
                second = true;
        }
        auto ps = board.get_adjacent_points(p, curr_piece);
        for (auto x: ps) {
            v.push_back(x);
            board.reset(x);
        }
        if (first && second) {
            return true;
        }
    }
    return false;
}

#endif