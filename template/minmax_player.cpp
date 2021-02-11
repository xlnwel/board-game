#include "minmax_player.hpp"


using namespace game;

template<typename Board>
std::function<bool(std::pair<std::size_t, Point>, std::pair<std::size_t, Point>)>
game::MinMaxPlayer<Board>::comp = [](std::pair<std::size_t, Point> x, std::pair<std::size_t, Point> y) {
    return x.first < y.first;
};