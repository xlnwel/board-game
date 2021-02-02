#include "state.hpp"
#include "game.hpp"

using namespace std;
using namespace game;

Game::Game(const Board& b, Piece p): init_state(b, p) {}

Game::Game(unique_ptr<Board>&& b, Piece p): init_state(std::move(b), p) {}

State Game::result(State state, Point m, Piece p) const {
    auto succ = state.update_board(m, p);
    if (succ) {
        auto u = compute_utility(state);
        state.update_utility(u);
    }
    return state;
}

int Game::compute_utility(const State& state) const {
    return state.is_over();
}

void game::play(const Game& g, const Player* p1, const Player* p2) {
    auto s = g.get_initial_state();
    assert(p1->get_piece() != p2->get_piece());
    if (p1->get_piece() != s.to_move())
        swap(p1, p2);
    size_t i = 0;
    Point m;
    Piece p;
    while (!g.terminal_test(s)) {
        s.display();
        if (i % 2 == 0) {
            m = p1->get_move(g, s);
            p = p1->get_piece();
        }
        else {
            m = p2->get_move(g, s);
            p = p2->get_piece();
        }
        s = g.result(s, m, p);
        i = (i+1) % 2;
    }
    s.display();
    cout << get_piece_color(s.get_piece()) << " won!\n";
    cout << "Valid moves: " << s.get_valid_moves().size() << '\n';
    cout << get_piece_color(p1->get_piece()) << " utility: " << s.get_utility(p1->get_piece()) << '\n';
    cout << get_piece_color(p2->get_piece()) << " utility: " << s.get_utility(p2->get_piece()) << '\n';
}
