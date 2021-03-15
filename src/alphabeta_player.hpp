#ifndef GAME_ALPHABETA_PLAYER_H_
#define GAME_ALPHABETA_PLAYER_H_

#include <utility>
#include "state.hpp"
#include "player.hpp"
#include "game.hpp"

namespace game {
    class AlphaBetaPlayer: public Player {
    public:
        AlphaBetaPlayer(Piece p): Player(p) {}

        Point get_move(const Game&, const State&) const override;
    private:
        int min_value(const Game&, const State&, int, int) const;
        int max_value(const Game&, const State&, int, int) const;
    };
}

#endif
