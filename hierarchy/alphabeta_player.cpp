#include <limits>
#include "alphabeta_player.hpp"

using namespace std;
using namespace game;


static bool comp(pair<int, Point>  x, pair<int, Point> y){
    return x.first < y.first;
};

Point AlphaBetaPlayer::get_move(const Game& game, const State& state) const {
    assert(!game.terminal_test(state));
    assert(state.to_move() == get_piece());
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    int best_util = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();
    int v;
    Point best_move;
    for (auto m: moves) {
        v = min_value(game, game.result(state, m, piece), best_util, beta);
        if (v > best_util) {
            best_util = v;
            best_move = m;
        }
    }
    return best_move;
}

int AlphaBetaPlayer::min_value(const Game& game, const State& state, int alpha, int beta) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    int v;
    for (auto m: moves) {
        v = max_value(game, game.result(state, m, piece), alpha, beta);
        if (v <= alpha)
            return v;
        beta = min(beta, v);
    }
    return v;
}

int AlphaBetaPlayer::max_value(const Game& game, const State& state, int alpha, int beta) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    int v; 
    for (auto m: moves) {
        v = min_value(game, game.result(state, m, piece), alpha, beta);
        if (v >= beta)
            return v;
        alpha = max(alpha, v);
    }
    return v;
}
