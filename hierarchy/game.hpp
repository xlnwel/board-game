#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <array>
#include <vector>
#include <memory>

# include "board.hpp"
# include "state.hpp"
# include "player.hpp"

namespace game {
    class Game {
    public:
        Game(const Board& b, Piece p=Piece::Blank);
        Game(std::unique_ptr<Board>&& b, Piece p=Piece::Blank);

        void play(const Player*, const Player*) const;
        bool terminal_test(const State& s) const { return s.get_utility() != 0 || s.get_valid_moves().empty(); }
        // copy the state, update it and return
        State result(State, Point, Piece) const;
        State get_initial_state() const { return init_state; }
    private:
        int compute_utility(const State&) const;
        State init_state;
    };
}

#endif
