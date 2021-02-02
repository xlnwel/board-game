#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "state.hpp"


namespace game {
    class Game;
    class Player {
    public:
        Player(Piece p): piece(p) {}

        virtual Point get_move(const Game&, const State&) const = 0;
        Piece get_piece() const { return piece; }
    private:
        Piece piece;
    };
}

#endif
