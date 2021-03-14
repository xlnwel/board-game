#ifndef GAME_ALPHABETA_CUTOOF_PLAYER_H_
#define GAME_ALPHABETA_CUTOOF_PLAYER_H_

#include <utility>
#include "state.hpp"
#include "player.hpp"
#include "game.hpp"

namespace game {
    class AlphaBetaCutOffPlayer: public Player {
    public:
        AlphaBetaCutOffPlayer(Piece p, int n): Player(p), cutoff(n) {}

        Point get_move(const Game&, const State&) const override;
    private:
        int min_value(const Game&, const State&, int, int, int) const;
        int max_value(const Game&, const State&, int, int, int) const;
        int cutoff;
    };
}

#endif
