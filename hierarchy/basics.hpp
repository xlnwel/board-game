#ifndef GAME_BASICS_H_
#define GAME_BASICS_H_

#include <string>
#include <utility>


namespace game {
    enum class Piece {Blank, White, Black};
    using Point = std::pair<std::size_t, std::size_t>;

    Piece next_piece(Piece);
    std::string get_piece_color(Piece p);

    struct PointHash{
        std::size_t operator() (const Point &p) const noexcept {
            return std::hash<std::size_t>{}(p.first) ^ (std::hash<std::size_t>{}(p.second) << 1);
        }
    };
}

#endif
