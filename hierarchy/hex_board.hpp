#ifndef GAME_HEX_BOARD_H_
#define GAME_HEX_BOARD_H_

#include <array>
#include "board.hpp"

namespace game {
    constexpr std::array<Point, 6> HexNeighbor{
        std::make_pair(-1, 0), 
        std::make_pair(-1, 1),
        std::make_pair(0, -1),
        std::make_pair(0, 1),
        std::make_pair(1, 0),
        std::make_pair(1, -1),
    };

    class HexBoard: public RhombusBoard {
    public:
        explicit HexBoard(std::size_t nn=11): RhombusBoard(nn) {}

        void display(std::ostream& os=std::cout) const final;
        HexBoard* clone() const final { return new HexBoard(*this);}

        bool is_over(Point, Piece) const final;
    private:
        bool is_xy_valid(std::size_t i, std::size_t j) const final { return get_xy_piece(i, j) == Piece::Blank; }
        std::vector<Point> get_adjacent_points(Point p, Piece piece) const;
    };
}

#endif