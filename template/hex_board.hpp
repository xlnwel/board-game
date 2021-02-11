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

    class HexBoard: public Board<HexBoard> {
    public:
        friend Board<HexBoard>;
        explicit HexBoard(std::size_t nn=11): Board<HexBoard>(nn) {}
        HexBoard(const HexBoard& other): Board<HexBoard>(other) {} 
        HexBoard(HexBoard&& other): Board<HexBoard>(std::move(other)) {}

        HexBoard& operator=(const HexBoard& rhs) {
            Board<HexBoard>::operator=(rhs); return *this; }
        HexBoard& operator=(HexBoard&& rhs) {
            Board<HexBoard>::operator=(rhs); return *this; }

        ~HexBoard() {}

        void display() const;

        // Functions for Hex
        std::vector<Point> get_adjacent_points(Point p, Piece piece) const;
    private:
        bool is_xy_valid(std::size_t i, std::size_t j) const { return get_piece(i, j) == Piece::Blank; }
    };
}

#endif