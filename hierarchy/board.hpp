#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>
#include <string>
#include <utility>

#include "basics.hpp"

namespace game {
    class Board {
    public:
        virtual ~Board() {}

        virtual void display(std::ostream& os=std::cout) const = 0;
        virtual Board* clone() const = 0;

        /* Queries */
        virtual Result result(Point, Piece) const = 0;
        bool is_on_board(Point p) const { return is_xy_on_board(p.first, p.second); }
        bool is_valid(Point p) const { return is_xy_valid(p.first, p.second); }

        /* Access */
        virtual std::vector<Point> get_valid_moves() const = 0;
        Piece get_piece(Point p) const { return get_xy_piece(p.first, p.second); }

        /* Modifiers */
        virtual bool reset(Point) = 0;
        virtual bool move(Point, Piece) = 0;
    protected:
        virtual bool is_xy_on_board(std::size_t, std::size_t) const = 0;
        virtual bool is_xy_valid(std::size_t, std::size_t) const = 0;
        virtual Piece get_xy_piece(std::size_t, std::size_t) const = 0;
    };

    class RhombusBoard: public Board {
    public:
        explicit RhombusBoard(std::size_t nn);

        /* Access */
        std::vector<Point> get_valid_moves() const override;

        /* Modifiers */
        bool reset(Point) override;
        bool move(Point, Piece) override;
    protected:
        bool is_xy_on_board(std::size_t i, std::size_t j) const final { return i >= 0 && i < n && j >= 0 && j < n; }
        Piece get_xy_piece(std::size_t i, std::size_t j) const final { return board[xy2idx(i, j)]; }

        const std::vector<Piece>& get_board() const { return board; }
        std::size_t get_board_size() const { return n; }
        std::size_t xy2idx(std::size_t i, std::size_t j) const { return i * n + j; }
    private:
        std::size_t n;
        std::vector<Piece> board;
    };

    std::ostream& operator<<(std::ostream& os, const Board& board);
    std::unique_ptr<Board> make_board(const std::string& type, int n);
}

#endif
