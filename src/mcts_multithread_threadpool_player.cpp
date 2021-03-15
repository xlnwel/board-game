#include <cmath>
#include <limits>
#include <random>
#include <future>

#include "../thread/thread_pool.hpp"
#include "mcts_multithread_threadpool_player.hpp"

using namespace std;
using namespace game;
using namespace thread_utils;


MCTSMultiThreadThreadPoolPlayer::MCTSMultiThreadThreadPoolPlayer(
    Piece p, int nn, double cc): Player(p), n(nn), c(cc) {}

Point MCTSMultiThreadThreadPoolPlayer::get_move(
        const Game& game, const State& state) const {
    assert(!state.is_over());
    auto root = make_unique<Node>(state);
    auto n_threads = std::thread::hardware_concurrency() - 1;
    {
        ThreadPool<void()> tp(n_threads);
        vector<future<void>> v(n_threads);
        int sim_per_thread = n / (n_threads+1);
        auto task = [this](const Game& game, Node* root, int sim_per_thread) {
            for (auto i = 0; i != sim_per_thread; ++i) {
                auto leaf = select_expand(game, root);
                auto result = simulate(game, leaf->state);
                backup(leaf, result);
            }
        };
        for (auto i = 0; i != n_threads - 1; ++i) {
            v[i] = tp.submit(task, game, root.get(), sim_per_thread);
        }
        task(game, root.get(), n - sim_per_thread * n_threads);
        for (auto& f: v)
            f.get();
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

double MCTSMultiThreadThreadPoolPlayer::ucb(Node* p) const {
    // traditional ucb
    if (p) {
        lock_guard lk{p->m};
        return p->utility / p->n + c * sqrt(log(p->parent->n) / p->n);
    }
    return numeric_limits<double>::max();
}

MCTSMultiThreadThreadPoolPlayer::Node* MCTSMultiThreadThreadPoolPlayer::select_expand(const Game& game, Node* p) const {
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

int MCTSMultiThreadThreadPoolPlayer::simulate(const Game& game, const State& s) const {
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

void MCTSMultiThreadThreadPoolPlayer::backup(Node* p, int v) const {
    assert(p);
    {
        lock_guard lk(p->m);
        ++p->n;
        p->utility += v;
    }
    if (p->parent)
        backup(p->parent, v);
}
void MCTSMultiThreadThreadPoolPlayer::make_child(const Game& game, Node* p, int idx) const {
    assert(p);
    auto moves = p->state.get_valid_moves();
    auto piece = p->state.to_move();
    auto state = game.result(p->state, moves[idx], piece);
    lock_guard lk(p->m);
    if (!p->children[idx]) {
        p->children[idx] = make_unique<Node>(std::move(state), p);
    }
}