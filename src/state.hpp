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
        State(const Board&, Piece=Piece::Blank, Point={});
        State(std::unique_ptr<Board>&&, Piece=Piece::Blank, Point={});
        State(const State&);
        State(State&&);
        
        State& operator=(const State&);
        State& operator=(State&&);
        
        void display(std::ostream& os=std::cout) const;

        /* Access */
        bool is_over() const { return utility != 0 || get_valid_moves().empty(); }
        std::unique_ptr<Board> copy_board() const;
        double get_utility() const { return utility; }
        // get utility for piece p
        double get_utility(Piece p) const { return p == curr_piece? utility: -utility; }
        void compute_utility() const;
        Piece get_piece() const { return curr_piece; }
        Piece to_move() const { return next_piece(curr_piece); }
        const std::vector<Point>& get_valid_moves() const { return valid_moves; }
    private:
        std::unique_ptr<Board> board;
        Piece curr_piece;
        Point curr_move;
        mutable double utility;
        std::vector<Point> valid_moves;
    };

    std::ostream& operator<<(std::ostream&, const State&);
}

#endif
