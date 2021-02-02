#ifndef GAME_MINMAX_PLAYER_H_
#define GAME_MINMAX_PLAYER_H_

#include <utility>
#include "state.hpp"
#include "player.hpp"
#include "game.hpp"

namespace game {
    class MinMaxPlayer: public Player {
    public:
        MinMaxPlayer(Piece p): Player(p) {}

        Point get_move(const Game&, const State&) const override;
    private:
        int min_value(const Game&, const State&) const;
        int max_value(const Game&, const State&) const;
    };
}

#endif
