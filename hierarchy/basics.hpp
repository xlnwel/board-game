#ifndef GAME_BASICS_H_
#define GAME_BASICS_H_

#include <iostream>
#include <string>
#include <utility>


namespace game {
    enum class Piece {Blank, White, Black};
    using Point = std::pair<std::size_t, std::size_t>;
    enum class Result {Win, Loss, Unknown};

    Piece next_piece(Piece);
    std::string get_piece_color(Piece p);
    int compute_score(Result);

    struct PointHash{
        std::size_t operator() (const Point &p) const noexcept {
            return std::hash<std::size_t>{}(p.first) ^ (std::hash<std::size_t>{}(p.second) << 1);
        }
    };

    std::ostream& operator<<(std::ostream&, Point);
    std::ostream& operator<<(std::ostream&, Piece);
    std::ostream& operator<<(std::ostream&, Result);
}

#endif
