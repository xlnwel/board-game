#include "minmax_player.hpp"

using namespace std;
using namespace game;


static bool comp(pair<int, Point>  x, pair<int, Point> y){
    return x.first < y.first;
};

Point MinMaxPlayer::get_move(const Game& game, const State& state) const {
    assert(!state.is_over());
    assert(state.to_move() == get_piece());
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    auto max_val = numeric_limits<int>::min();
    auto v = max_val;
    auto best_move = *moves.begin();
    for (auto m: moves) {
        if ((v = min_value(game, game.result(state, m, piece))) > max_val) {
            max_val = v;
            best_move = m;
            if (max_val > 0)   // NOTE: this can speed up 5+x inference, but only suitable for win-loss game
                break;
        }
    }
    return best_move;
}

int MinMaxPlayer::min_value(const Game& game, const State& state) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    auto min_val = numeric_limits<int>::max();
    auto v = min_val;
    for (auto m: moves) {
        if ((v = max_value(game, game.result(state, m, piece))) < min_val) {
            min_val = v;
        }
    }
    return min_val;
}

int MinMaxPlayer::max_value(const Game& game, const State& state) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    const auto& moves = state.get_valid_moves();
    auto piece = state.to_move();
    auto max_val = numeric_limits<int>::min();
    auto v = max_val;
    for (auto m: moves) {
        if ((v = min_value(game, game.result(state, m, piece))) > max_val) {
            max_val = v;
        }
    }
    return max_val;
}
