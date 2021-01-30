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

    std::vector<Point> get_adjacent_points_hex(const Board::type&, Point, Piece);

    class HexBoard: public Board {
    public:
        explicit HexBoard(int n=11);
        HexBoard(const HexBoard&);
        HexBoard(HexBoard&&);

        HexBoard& operator=(const HexBoard&);
        HexBoard& operator=(HexBoard&&);

        ~HexBoard() {}

        void display() const final;

        // Functions for Hex
        std::vector<Point> get_adjacent_points(Point p, Piece piece) const;
    private:
        bool is_valid(int i, int j) const final { return get_piece(i, j) == Piece::Blank; }
    };
}

#endif