#ifndef GAME_MINMAX_PLAYER_H_
#define GAME_MINMAX_PLAYER_H_

#include <vector>
#include <utility>
#include <algorithm>
#include "state.hpp"
#include "player.hpp"
#include "game.hpp"

namespace game {
    template<typename Board>
    class MinMaxPlayer: public Player<Board> {
    public:
        MinMaxPlayer(Piece p): Player<Board>(p) {}

        Point operator()(const Game<Board>&, const State<Board>&);
    private:
        using util_move = std::pair<std::size_t, Point>;
        static std::function<bool(util_move, util_move)> comp;
        util_move min_value(const Game<Board>&, const State<Board>&);
        util_move max_value(const Game<Board>&, const State<Board>&);
    };
}

template<typename Board>
game::Point game::MinMaxPlayer<Board>::operator()(
        const Game<Board>& game, const State<Board>& state) {
    auto [util, move] = max_value(game, state);
    return move;
}

template<typename Board>
typename game::MinMaxPlayer<Board>::util_move 
game::MinMaxPlayer<Board>::min_value(
        const Game<Board>& game, const State<Board>& state) {
    auto util = game.compute_utility(state, Player<Board>::get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    std::vector<util_move> v; 
    for (auto m: moves) {
        v.push_back(max_value(game, game.result(state, m, piece)), m);
    }
    auto itr = std::min_element(v.begin(), v.end(), comp);
    return *itr;
}

template<typename Board>
typename game::MinMaxPlayer<Board>::util_move 
game::MinMaxPlayer<Board>::max_value(
        const Game<Board>& game, const State<Board>& state) {
    auto util = game.compute_utility(state, Player<Board>::get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    std::vector<util_move> v; 
    for (auto m: moves) {
        v.push_back(min_value(game, game.result(state, m, piece)), m);
    }
    auto itr = std::max_element(v.begin(), v.end(), comp);
    return *itr;
}

#endif
