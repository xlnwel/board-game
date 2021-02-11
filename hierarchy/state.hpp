#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>

#include "basics.hpp"

namespace game {
    class Board;
    class State {
    public:
        State(const Board& b, Piece p=Piece::Blank, std::size_t u=0);
        State(std::unique_ptr<Board>&& b, Piece p=Piece::Blank, std::size_t u=0);
        State(const State&);
        State(State&&);
        
        State& operator=(const State&);
        State& operator=(State&&);
        
        void display(std::ostream& os=std::cout) const;
        bool is_over() const;

        /* Modifiers */
        bool update_board(Point, Piece);
        void update_utility(std::size_t u);

        /* Access */
        int get_utility() const { return utility; }
        // get utility for piece p
        int get_utility(Piece p) const { return p == curr_piece? utility: -utility; }
        Piece get_piece() const { return curr_piece; }
        Piece to_move() const { return next_piece(curr_piece); }
        std::unordered_set<Point, PointHash> get_valid_moves() const { return valid_moves; }
    private:
        Piece curr_piece;
        std::unique_ptr<Board> board;
        std::size_t utility;
        Point curr_move;
        std::unordered_set<Point, PointHash> valid_moves;
    };

    std::ostream& operator<<(std::ostream&, const State&);
}

#endif
