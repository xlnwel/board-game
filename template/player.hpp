#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "state.hpp"
#include "game.hpp"


namespace game {
    template<typename Board>
    class Player {
    public:
        Player(Piece p): piece(p) {}

        Point operator()(const Game<Board>&, const State<Board>&);
    protected:
        Piece get_piece() const { return piece; }
    private:
        Piece piece;
    };
}

#endif
