#ifndef GAME_MCTS_MULTITHREAD_LOCKFREE_PLAYER_H_
#define GAME_MCTS_MULTITHREAD_LOCKFREE_PLAYER_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "state.hpp"
#include "player.hpp"
#include "game.hpp"

namespace game {
    class MCTSMultiThreadLockFreePlayer: public Player {
    public:
        MCTSMultiThreadLockFreePlayer(Piece p, int nn, double cc=1.4);

        Point get_move(const Game&, const State&) const override;
    private:
        struct Node {
            Node(const State& s, Node* p=nullptr): 
                state(s), parent(p), 
                children(state.get_valid_moves().size()), 
                n(0), utility(0) {}
            Node(State&& s, Node* p=nullptr): 
                state(std::move(s)), parent(p), 
                children(state.get_valid_moves().size()),
                n(0), utility(0) {}
            
            State state;
            Node* parent;
            std::vector<std::unique_ptr<Node>> children;
            std::atomic_size_t n;
            std::atomic<double> utility;
            std::mutex m;
        };
        double ucb(Node* p) const;
        Node* select_expand(const Game&, Node*) const;
        int simulate(const Game&, const State&) const;
        void backup(Node*, int) const;
        void make_child(const Game&, Node*, int) const;
        int n;  // number of simulations
        double c;
    };
}

#endif
