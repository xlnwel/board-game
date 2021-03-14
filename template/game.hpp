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

        // copy the state, update it and return
        State<Board> result(State<Board>, Point, Piece) const;
        // update the game's internal state
        State<Board> result(Point, Piece);
    };
}

template<typename Board>
game::State<Board> game::Game<Board>::result(
        game::State<Board> state, game::Point m, game::Piece p) const {
    auto succ = state.update_board(m, p);
    if (succ) {
        state.update_utility(u);
    }
    return state;
}

#endif