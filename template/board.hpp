#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>
#include <unordered_set>
#include <string>
#include <utility>

#include "basics.hpp"

namespace game {
    /* Adopt CRTP to avoid virtual functions in hierarchy 
    and to allow to introduce new methods in derived classes 
    */
    template<typename GameType>
    class Board {
    public:
        using type = std::vector<std::vector<Piece>>;
        explicit Board(std::size_t);
        Board(const Board&);
        Board(Board&&);

        Board& operator=(const Board&);
        Board& operator=(Board&&);

        ~Board() {}

        void display() const { return static_cast<const GameType*>(this)->display(); }

        /* Queries */
        bool is_on_board(Point p) const { return is_on_board(p.first, p.second); }
        bool is_valid(Point p) const { return static_cast<const GameType*>(this)->is_valid(p.first, p.second); }
        
        /* Access */
        std::unordered_set<Point, PointHash> get_valid_moves();
        Piece get_piece(Point p) const { return get_piece(p.first, p.second); }
        std::size_t get_board_size() const { return n; }

        /* Modifiers */
        bool reset(Point);
        bool move(Point, Piece);
    protected:
        bool is_on_board(std::size_t i, std::size_t j) const { return i >= 0 && i < n && j >= 0 && j < n; }
        bool is_xy_valid(std::size_t i, std::size_t j) const { return static_cast<const GameType*>(this)->is_xy_valid(i, j); }

        const type& get_board() const { return board; }
        Piece get_piece(std::size_t i, std::size_t j) const { return board[i][j]; }
    private:
        std::size_t n;
        type board;
    };
}

template<typename GameType>
game::Board<GameType>::Board(std::size_t nn): n(nn), board(nn, std::vector<Piece>(nn, Piece::Blank)) {
    assert(n > 0);
}

template<typename GameType>
game::Board<GameType>::Board(const Board& other): n(other.n), board(other.board) {}

template<typename GameType>
game::Board<GameType>::Board(Board&& other): n(other.n), board(std::move(other.board)) {}

template<typename GameType>
game::Board<GameType>& game::Board<GameType>::operator=(const Board& rhs) {
    if (this != &rhs) {
        n = rhs.n;
        board = rhs.board;
    }
    return *this;
}

template<typename GameType>
game::Board<GameType>& game::Board<GameType>::operator=(Board&& rhs) {
    if (this != &rhs) {
        n = rhs.n;
        board = std::move(rhs.board);
    }
    return *this;
}

template<typename GameType>
bool game::Board<GameType>::reset(Point p) {
    std::size_t i = p.first, j = p.second;
    if (!is_on_board(i, j))
        return false;
    board[i][j] = Piece::Blank;
    return true;
}

template<typename GameType>
bool game::Board<GameType>::move(Point p, Piece piece) {
    std::size_t i = p.first, j = p.second;
    if (!is_on_board(i, j) || !is_xy_valid(i, j))
        return false;
    board[i][j] = piece;
    return true;
}

template<typename GameType>
std::unordered_set<game::Point, game::PointHash> game::Board<GameType>::get_valid_moves() {
    std::unordered_set<Point, PointHash> valid_moves;
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t j = 0; j != n; ++j) {
            if (is_xy_valid(i, j))
                valid_moves.emplace(i, j);
        }
    }
    return valid_moves;
}

#endif
