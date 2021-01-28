#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <array>
#include <vector>
#include <string>
#include <utility>

#include "basics.hpp"

namespace game {    
    class Board {
    public:
        explicit Board(int);
        Board(const Board&);
        Board(Board&&);

        Board& operator=(const Board&);
        Board& operator=(Board&&);

        virtual ~Board() {}

        virtual void display() const = 0;
        bool is_on_board(Point p) const { return is_on_board(get<0>(p), get<1>(p)); }
        bool is_valid(Point p) const { return is_valid(get<0>(p), get<1>(p)); }
        std::vector<Point> get_valid_moves() const;

        bool move(Point, Piece);
    protected:
        bool is_on_board(int i, int j) const { return i >= 0 && i < n && j >= 0 && j < n; }
        virtual bool is_valid(int i, int j) const = 0;
        const std::vector<std::vector<Piece>>& get_board() const { return board; }
        Piece get_piece(int i, int j) const { return board[i][j]; }
        int get_board_size() const { return n; }
    private:
        int n;
        std::vector<std::vector<Piece>> board;
    };
}

#endif