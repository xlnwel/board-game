#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>
#include <unordered_set>
#include <string>
#include <utility>

#include "basics.hpp"

namespace game {    
    class Board {
    public:
        using type = std::vector<std::vector<Piece>>;
        explicit Board(int);
        Board(const Board&);
        Board(Board&&);

        Board& operator=(const Board&);
        Board& operator=(Board&&);

        virtual ~Board() {}

        virtual void display() const = 0;

        /* Queries */
        bool is_on_board(Point p) const { return is_on_board(p.first, p.second); }
        bool is_valid(Point p) const { return is_valid(p.first, p.second); }
        
        /* Access */
        std::unordered_set<Point, PointHash> get_valid_moves();
        Piece get_piece(Point p) const { return get_piece(p.first, p.second); }
        int get_board_size() const { return n; }

        /* Modifiers */
        bool reset(Point);
        bool move(Point, Piece);
    protected:
        bool is_on_board(int i, int j) const { return i >= 0 && i < n && j >= 0 && j < n; }
        virtual bool is_valid(int i, int j) const = 0;

        const type& get_board() const { return board; }
        Piece get_piece(int i, int j) const { return board[i][j]; }
    private:
        int n;
        type board;
    };
}

#endif
