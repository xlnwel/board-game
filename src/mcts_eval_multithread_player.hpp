#ifndef GAME_MCTS_EVALUATION_MULTITHREAD_PLAYER_H_
#define GAME_MCTS_EVALUATION_MULTITHREAD_PLAYER_H_

#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "game.hpp"
#include "player.hpp"
#include "state.hpp"

namespace game {
    class MCTSEvaluationMultiThreadPlayer: public Player {
    public:
        MCTSEvaluationMultiThreadPlayer(Piece p, int nn, double cc=1.4);

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
            std::size_t n;
            double utility;
            std::mutex m;
        };
        double ucb(Node* p) const;
        Node* select_expand(const Game&, Node*) const;
        double simulate(const Game&, const State&) const;
        void backup(Node*, double) const;
        void make_child(const Game&, Node*, int) const;
        int n;  // number of simulations
        double c;
    };
}

#endif
