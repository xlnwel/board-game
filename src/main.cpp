#include <algorithm>
#include <array>
#include <chrono>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <ios>
#include <memory>
#include <utility>

#include "alphabeta_player.hpp"
#include "alphabeta_cutoff_player.hpp"
#include "minmax_player.hpp"
#include "mcts_player.hpp"
#include "mcts_eval_multithread_player.hpp"
#include "mcts_multithread_player.hpp"
#include "mcts_multithread_threadpool_player.hpp"

#include "board.hpp"
#include "game.hpp"
#include "state.hpp"
#include "utils.hpp"


using namespace game;
using namespace std;
using namespace utility;

string ask_for_player_type(int player_idx) {
    string pt;
    cout << "Select player" << player_idx << "(AlphaBeta AlphaBetaCutOff MCTS MCTSEMT MCTSMT MinMax): ";
    cin >> pt;
    transform(pt.begin(), pt.end(), pt.begin(), ::toupper);
    return pt;
}

int ask_for_n(const string& p, int player_idx) {
    if (p == "ALPHABETA" || p == "MINMAX")
        return 0;
    string s;
    if (p == "ALPHABETACUTOFF") {
        s = "The depth to cutoff";
    }
    else {
        s = "The number of simulations";
    }
    cout << "(Player" << player_idx <<")" + s + ": ";
    int n;
    cin >> n;
    return n;
}

int ask_for_experiments() {
    cout << "Number of experiments: ";
    int n;
    cin >> n;
    return n;
}

unique_ptr<Player> create_player(const string& s, Piece p, int n) {
    if (s == "ALPHABETA")
        return make_unique<AlphaBetaPlayer>(p);
    if (s == "ALPHABETACUTOFF")
        return make_unique<AlphaBetaCutOffPlayer>(p, n);
    if (s == "MCTS")
        return make_unique<MCTSPlayer>(p, n);
    if (s == "MCTSMT")
        return make_unique<MCTSMultiThreadPlayer>(p, n);
    if (s == "MCTSEMT")
        return make_unique<MCTSEvaluationMultiThreadPlayer>(p, n);
    if (s == "MCTSMTTP")
        return make_unique<MCTSMultiThreadThreadPoolPlayer>(p, n);
    if (s == "MINMAX")
        return make_unique<MinMaxPlayer>(p);
    throw invalid_argument("Invalid player type: " + s);
}

void print_win_rate(const Game& g, const string& p_type, const Player* p) {
    cout << get_piece_color(p->get_piece()) << "(" << p_type
        << ") win rate: " << g.compute_win_rate(p->get_piece())
        << "\n";
}

int main() {
    cout << "Board size: ";
    size_t n;
    cin >> n;
    auto p1_type = ask_for_player_type(1);
    auto p2_type = ask_for_player_type(2);
    int n1 = ask_for_n(p1_type, 1);
    int n2 = ask_for_n(p2_type, 2);

    auto p1 = create_player(p1_type, Piece::White, n1);
    auto p2 = create_player(p2_type, Piece::Black, n2);
    int n_exps = ask_for_experiments();
    // int n = 9;
    // string p1_type = "MCTS";
    // string p2_type = "MCTS";
    // auto p1 = make_unique<MCTSMultiThreadThreadPoolPlayer>(Piece::White, 1000);
    // auto p2 = make_unique<MCTSMultiThreadThreadPoolPlayer>(Piece::Black, 1000);
    string description = "Time to run (" + p1_type + " vs " + p2_type + 
        ") on (" + to_string(n) + " x " + to_string(n) + ") board: ";
    Game g(make_board("Hex", n)); 
    for (auto i = 0; i != n_exps; ++i) {
        timeit(description, &g, &Game::play, p1.get(), p2.get());
    }
    print_win_rate(g, p1_type, p1.get());
    print_win_rate(g, p2_type, p2.get());
}
