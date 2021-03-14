#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <vector>
#include <memory>
#include <unordered_set>

#include "basics.hpp"

namespace game {
    template<typename Board>
    class State {
    public:
        State(Board={}, Piece=Piece::White, std::size_t u=0);
        State(const State&);
        State(State&&);
        
        State& operator=(const State&);
        State& operator=(State&&);

        ~State() {}
        
        void display() const { board.display(); }
        Result result() const;

        /* Modifiers */
        bool update_board(Point, Piece);
        void update_utility(std::size_t);

        /* Access */
        std::size_t get_utility() const { return utility; }
        // get utility for piece p
        std::size_t get_utility(Piece p) const { return p == curr_piece? utility: -utility; }
        Piece get_piece() const { return curr_piece; }
        Piece to_move() const { return next_piece(curr_piece); }
        const Board& get_board() const { return board; }
        std::vector<Point> get_valid_moves() { return valid_moves; }
    private:
        Piece curr_piece;
        Board board;
        std::size_t utility;
        Point curr_move;
        std::vector<Point> valid_moves;
    };
}

template<typename Board>
game::State<Board>::State(Board b, Piece p, std::size_t u):
        board(b), curr_piece(p), utility(u) {
    valid_moves = board.get_valid_moves();
}

template<typename Board>
game::State<Board>::State(const State& rhs): 
        curr_piece(rhs.curr_piece), 
        board(rhs.board),
        utility(rhs.utility),
        curr_move(rhs.curr_move) {
    
}

template<typename Board>
game::State<Board>::State(State&& rhs):
        curr_piece(rhs.curr_piece),
        board(std::move(rhs.board)),
        utility(rhs.utility),
        curr_move(rhs.curr_move) {
}

template<typename Board>
game::State<Board>& game::State<Board>::operator=(const State& rhs) {
    if (this != &rhs) {
        auto tmp = rhs;
        swap(*this, tmp);
    }
    return *this;
}

template<typename Board>
game::State<Board>& game::State<Board>::operator=(State&& rhs) {
    if (this != &rhs) {
        curr_piece = rhs.curr_piece;
        swap(board, rhs.board);
        utility = rhs.utility;
        curr_move = rhs.curr_move;
    }
    return *this;
}

template<typename Board>
bool game::State<Board>::update_board(Point point, Piece piece) {
    curr_piece = piece;
    curr_move = point;

    auto succ = board.move(point, piece);
    if (succ)
        valid_moves.erase(point);
    
    return succ;
}

template<typename Board>
void game::State<Board>::update_utility(std::size_t u) {
    utility = u;
}

#endif
