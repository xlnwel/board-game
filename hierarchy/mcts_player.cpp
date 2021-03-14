#include <cmath>
#include <limits>
#include <random>

#include "mcts_player.hpp"

using namespace std;
using namespace game;


MCTSPlayer::MCTSPlayer(Piece p, int nn, double cc):
    Player(p), n(nn), c(cc) {}

Point MCTSPlayer::get_move(const Game& game, const State& state) const {
    auto root = make_unique<Node>(state);
    for (auto i = 0; i != n; ++i) {
        auto leaf = select(game, root.get());
        auto child = expand(game, leaf);
        auto result = simulate(game, child->state);
        backup(child, result);
    }
    int max_i = 0;
    auto max_n = 0;
    const auto& moves = state.get_valid_moves();
    const auto& children = root->children;
    assert(moves.size() == children.size()); 
    for (auto i = 0; i != moves.size(); ++i) {
        if (children[i]->n > max_n)
            max_i = i;
    }
    return moves[max_i];
}

double MCTSPlayer::ucb(Node* p) const {
    // traditional ucb
    if (p)
        return p->utility / p->n + c * sqrt(log(p->parent->n) / p->n);
    return numeric_limits<double>::max();
}

MCTSPlayer::Node* MCTSPlayer::select(const Game& game, Node* p) const {
    vector<double> v(p->children.size());
    double max_val = numeric_limits<double>::min();
    int max_idx = 0;
    for (auto i = 0; i != p->children.size(); ++i) {
        v[i] = ucb(p->children[i].get());
        if (v[i] > max_val) {
            max_val = v[i];
            max_idx = i;
            if (max_val == numeric_limits<double>::max())
                break;
        }
    }
    if (!p->children[max_idx]) {
        make_child(game, p, max_idx);
    }
    return p->children[max_idx].get();
}

MCTSPlayer::Node* MCTSPlayer::expand(const Game& game, Node* p) const {
    if (p->children.empty())
        return p;
    make_child(game, p, 0);
    return p->children.begin()->get();
}

int MCTSPlayer::simulate(const Game& game, const State& s) const {
    if (s.get_valid_moves().empty())
        return s.get_utility(get_piece());
    auto state = game.result(s, *s.get_valid_moves().begin(), s.to_move());
    while (!state.is_over()) {
        state = game.result(
            state, 
            *state.get_valid_moves().begin(), 
            state.to_move());
    }
    return state.get_utility(get_piece());
}

void MCTSPlayer::backup(Node* p, int v) const {
    ++p->n;
    p->utility += v;
    if (p->parent)
        backup(p->parent, v);
}
void MCTSPlayer::make_child(const Game& game, Node* p, int idx) const {
    auto moves = p->state.get_valid_moves();
    auto piece = p->state.to_move();
    auto state = game.result(p->state, moves[idx], piece);
    p->children[idx] = make_unique<Node>(
        std::move(state),
        p);
}