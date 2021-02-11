#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <array>
#include <vector>

# include "state.hpp"

namespace game {
    template<typename Board>
    class Game {
    public:
        Game();
        ~Game() {}

        bool terminal_test(const State<Board>& s) const { return s.get_utility() != 0 || s.get_valid_moves().empty(); }
        // copy the state, update it and return
        State<Board> result(State<Board>, Point, Piece) const;
        // update the game's internal state
        State<Board> result(Point, Piece);
        
        std::size_t compute_utility(const State<Board>&, Piece) const;
    };
}

template<typename Board>
game::State<Board> game::Game<Board>::result(
        game::State<Board> state, game::Point m, game::Piece p) const {
    auto succ = state.update_board(m, p);
    if (succ) {
        auto u = compute_utility(state, p);
        state.update_utility(u);
    }
    return state;
}

template<typename Board>
std::size_t game::Game<Board>::compute_utility(const State<Board>& state, Piece p) const {
    // compute utility for p
    std::size_t util = state.is_over();
    if (p != state.get_piece())
        util *= -1;
    return util;
}

#endif