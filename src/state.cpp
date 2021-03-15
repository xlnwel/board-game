#include <sstream>
#include <stdexcept>

#include "state.hpp"
#include "board.hpp"

using namespace std;
using namespace game;


State::State(const Board& b, Piece p, Point m):
        State(unique_ptr<Board>(b.clone()), p, m) {}

State::State(unique_ptr<Board>&& b, Piece p, Point m):
        board(std::move(b)), curr_piece(p), curr_move(m) {
    utility = compute_score(board->result(m, p));
    valid_moves = board->get_valid_moves();
}

State::State(const State& rhs): 
        curr_piece(rhs.curr_piece), 
        board(rhs.board->clone()),
        utility(rhs.utility),
        curr_move(rhs.curr_move),
        valid_moves(rhs.valid_moves) {}

State::State(State&& rhs):
        curr_piece(rhs.curr_piece),
        board(std::move(rhs.board)),
        utility(rhs.utility),
        curr_move(rhs.curr_move),
        valid_moves(std::move(rhs.valid_moves)) {}

State& State::operator=(const State& rhs) {
    if (this != &rhs) {
        auto tmp = rhs;
        swap(*this, tmp);
    }
    return *this;
}

State& State::operator=(State&& rhs) {
    if (this != &rhs) {
        curr_piece = rhs.curr_piece;
        swap(board, rhs.board);
        utility = rhs.utility;
        curr_move = rhs.curr_move;
        swap(valid_moves, rhs.valid_moves);
    }
    return *this;
}

void State::display(ostream& os) const {
    board->display(os);
}

std::unique_ptr<Board> State::copy_board() const {
    return std::unique_ptr<Board>(board->clone());
}

ostream& game::operator<<(ostream& os, const State& state) {
    state.display(os);
    return os;
}

void State::compute_utility() const { 
    utility = board->compute_utility(curr_piece); 
}