#include "minmax_player.hpp"

using namespace std;
using namespace game;


static bool comp(pair<int, Point>  x, pair<int, Point> y){
    return x.first < y.first;
};

Point MinMaxPlayer::get_move(const Game& game, const State& state) const {
    assert(!game.terminal_test(state));
    assert(state.to_move() == get_piece());
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    std::vector<pair<int, Point>> v; 
    for (auto m: moves) {
        v.emplace_back(min_value(game, game.result(state, m, piece)), m);
    }
    auto itr = max_element(v.begin(), v.end(), comp);
    return itr->second;
}

int MinMaxPlayer::min_value(const Game& game, const State& state) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    std::vector<pair<int, Point>> v; 
    for (auto m: moves) {
        v.emplace_back(max_value(game, game.result(state, m, piece)), m);
    }
    auto itr = std::min_element(v.begin(), v.end(), comp);
    return itr->first;
}

int MinMaxPlayer::max_value(const Game& game, const State& state) const {
    auto util = state.get_utility(get_piece());
    if (util != 0)
        return util;
    auto moves = state.get_valid_moves();
    auto piece = state.to_move();
    std::vector<pair<int, Point>> v; 
    for (auto m: moves) {
        v.emplace_back(min_value(game, game.result(state, m, piece)), m);
    }
    auto itr = std::max_element(v.begin(), v.end(), comp);
    return itr->first;
}
