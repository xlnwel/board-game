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
        // copy the state, update it and return
        State result(const State&, Point, Piece) const;
        State get_initial_state() const { return init_state; }
    private:
        State init_state;
    };
}

#endif
