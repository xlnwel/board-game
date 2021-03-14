#include <cassert>
#include <sstream>

#include "basics.hpp"
#include "state.hpp"
#include "game.hpp"

using namespace std;
using namespace game;

Game::Game(const Board& b, Piece p): init_state(b, p) {}

Game::Game(unique_ptr<Board>&& b, Piece p): init_state(std::move(b), p) {}

State Game::result(const State& state, Point m, Piece p) const {
    auto new_board = state.copy_board();
    auto succ = new_board->move(m, p);
    if (succ) {
        State new_state(std::move(new_board), p, m);
        return new_state;
    }
    else {
        ostringstream oss;
        oss << p << " invalid move: " << m << "\nValid moves: ";
        for (auto m: state.get_valid_moves())
            oss << m << " ";
        throw std::logic_error(oss.str());
    }
    return state;
}

void Game::play(const Player* p1, const Player* p2) const {
    auto s = get_initial_state();
    assert(p1->get_piece() != p2->get_piece());
    if (p1->get_piece() != s.to_move())
        swap(p1, p2);
    size_t i = 0;
    Point m;
    Piece p;
    while (!s.is_over()) {
        // s.display();
        if (i % 2 == 0) {
            m = p1->get_move(*this, s);
            p = p1->get_piece();
        }
        else {
            m = p2->get_move(*this, s);
            p = p2->get_piece();
        }
        s = result(s, m, p);
        i = (i+1) % 2;
    }
    s.display();
    cout << get_piece_color(s.get_piece()) << " won!\n";
    cout << get_piece_color(p1->get_piece()) << " utility: " << s.get_utility(p1->get_piece()) << '\n';
    cout << get_piece_color(p2->get_piece()) << " utility: " << s.get_utility(p2->get_piece()) << '\n';
}
