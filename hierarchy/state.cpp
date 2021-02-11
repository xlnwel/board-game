#include "state.hpp"
#include "board.hpp"

using namespace std;
using namespace game;


State::State(const Board& b, Piece p, std::size_t u):
        board(b.clone()), curr_piece(p), utility(u) {
    valid_moves = board->get_valid_moves();
}

State::State(unique_ptr<Board>&& b, Piece p, std::size_t u):
        board(std::move(b)), curr_piece(p), utility(u) {
    valid_moves = board->get_valid_moves();
}

State::State(const State& rhs): 
        curr_piece(rhs.curr_piece), 
        board(rhs.board->clone()),
        utility(rhs.utility),
        curr_move(rhs.curr_move),
        valid_moves(rhs.valid_moves) {
    
}

State::State(State&& rhs):
        curr_piece(rhs.curr_piece),
        board(std::move(rhs.board)),
        utility(rhs.utility),
        curr_move(rhs.curr_move),
        valid_moves(std::move(rhs.valid_moves)) {
}

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

bool State::is_over() const { 
    return board->is_over(curr_move, curr_piece); 
}

bool State::update_board(Point point, Piece piece) {
    curr_piece = piece;
    curr_move = point;

    auto succ = board->move(point, piece);
    if (succ)
        valid_moves.erase(point);
    
    return succ;
}

void State::update_utility(size_t u) {
    utility = u;
}

ostream& game::operator<<(ostream& os, const State& state) {
    state.display(os);
    return os;
}
