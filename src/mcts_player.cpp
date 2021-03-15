#include <cmath>
#include <limits>
#include <random>

#include "mcts_player.hpp"

using namespace std;
using namespace game;


MCTSPlayer::MCTSPlayer(Piece p, int nn, double cc):
    Player(p), n(nn), c(cc) {}

Point MCTSPlayer::get_move(const Game& game, const State& state) const {
    assert(!state.is_over());
    auto root = make_unique<Node>(state);
    for (auto i = 0; i != n; ++i) {
        auto leaf = select_expand(game, root.get());
        auto result = simulate(game, leaf->state);
        backup(leaf, result);
    }
    int max_i = 0;
    auto max_n = 0;
    const auto& moves = state.get_valid_moves();
    const auto& children = root->children;
    assert(moves.size() == children.size()); 
    for (auto i = 0; i != moves.size(); ++i) {
        if (children[i] && children[i]->n > max_n)
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

MCTSPlayer::Node* MCTSPlayer::select_expand(const Game& game, Node* p) const {
    assert(p);
    assert(!p->children.empty());
    double max_val = numeric_limits<double>::min();
    int max_idx = 0;
    vector<double> v(p->children.size());
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
        make_child(game, p, max_idx);   // expansion happens here, introducing an additional expand could incur additional O(N) the memory, where N is the number of leaf nodes
        return p->children[max_idx].get();
    }
    else if (p->children[max_idx]->state.is_over()) {
        return p->children[max_idx].get();
    }
    else {
        return select_expand(game, p->children[max_idx].get());
    }
}

int MCTSPlayer::simulate(const Game& game, const State& s) const {
    if (s.is_over())
        return s.get_utility(get_piece());
    assert(!s.get_valid_moves().empty());
    auto state = game.result(s, s.get_valid_moves()[0], s.to_move());
    while (!state.is_over()) {
        state = game.result(
            state, 
            state.get_valid_moves()[0], 
            state.to_move());
    }
    return state.get_utility(get_piece());
}

void MCTSPlayer::backup(Node* p, int v) const {
    assert(p);
    ++p->n;
    p->utility += v;
    if (p->parent)
        backup(p->parent, v);
}
void MCTSPlayer::make_child(const Game& game, Node* p, int idx) const {
    assert(p);
    auto moves = p->state.get_valid_moves();
    auto piece = p->state.to_move();
    auto state = game.result(p->state, moves[idx], piece);
    p->children[idx] = make_unique<Node>(std::move(state), p);
}