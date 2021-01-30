#ifndef GAME_BASICS_H_
#define GAME_BASICS_H_

#include <string>
#include <utility>


namespace game {
    enum class Piece {Blank, White, Black};
    using Point = std::pair<int, int>;

    Piece next_piece(Piece);
    std::string get_piece_color(Piece p);

    struct PointHash{
        std::size_t operator() (const Point &p) const noexcept {
            return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
        }
    };
}

#endif
