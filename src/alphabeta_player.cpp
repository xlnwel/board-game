#include <cassert>
#include <limits>
#include "alphabeta_player.hpp"

using namespace std;
using namespace game;


static bool comp(pair<int, Point>  x, pair<int, Point> y){
    return x.first < y.first;
};

Point AlphaBetaPlayer::get_move(const Game& game, const State& state) const {
    assert(!state.is_over());
    assert(state.to_move() == get_piece());
    const auto& moves = state.get_valid_moves();
    assert(!moves.empty());
    auto piece = state.to_move();
    assert(get_piece() == piece);
    auto alpha = numeric_limits<int>::min();
    auto beta = numeric_limits<int>::max();
    auto v = alpha;
    auto best_val = alpha;
    auto best_move = *moves.begin();
    for (auto m: moves) {
        v = min_value(game, game.result(state, m, piece), alpha, beta);
        if (v > alpha) {
            alpha = v;
            if (v > best_val) {
                best_move = m;
                best_val = v;
            }
        }
    }
    return best_move;
}

int AlphaBetaPlayer::min_value(const Game& game, const State& state, int alpha, int beta) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    auto v = beta;
    auto min_val = beta;
    for (auto m: moves) {
        v = max_value(game, game.result(state, m, piece), alpha, beta);
        if (v <= alpha)
            return v;
        if (v < beta) {
            beta = v;
            if (v < min_val) {
                min_val = v;
            }
        }
    }
    return min_val;
}

int AlphaBetaPlayer::max_value(const Game& game, const State& state, int alpha, int beta) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    auto v = alpha; 
    auto max_val = alpha;
    for (auto m: moves) {
        v = min_value(game, game.result(state, m, piece), alpha, beta);
        if (v >= beta)
            return v;
        if (v > alpha) {
            alpha = v;
            if (v > max_val) {
                max_val = v;
            }
        }
    }
    return max_val;
}
