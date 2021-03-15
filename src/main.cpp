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
    cout << "Select player" << player_idx << "(AlphaBeta AlphaBetaCutOff MCTS MCTSMT MinMax): ";
    cin >> pt;
    transform(pt.begin(), pt.end(), pt.begin(), ::toupper);
    return pt;
}

int ask_for_n(const string& p, int player_idx) {
    if (p == "ALPHABETA" || p == "MINMAX")
        return 0;
    cout << "Player" << player_idx <<"-the number of simulations/The depth to cutoff: ";
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
    if (s == "MCTSMTTP")
        return make_unique<MCTSMultiThreadThreadPoolPlayer>(p, n);
    if (s == "MINMAX")
        return make_unique<MinMaxPlayer>(p);
    throw invalid_argument("Invalid player type: " + s);
}

int main() {
    cout << "Board size: ";
    size_t n;
    cin >> n;
    string p1_type = ask_for_player_type(1);
    string p2_type = ask_for_player_type(2);
    int n1 = ask_for_n(p1_type, 1);
    int n2 = ask_for_n(p2_type, 2);

    auto p1 = create_player(p1_type, Piece::White, n1);
    auto p2 = create_player(p2_type, Piece::Black, n2);
    // int n = 5;
    // string p1_type = "MCTS";
    // string p2_type = "MCTS";
    // auto p1 = make_unique<MCTSPlayer>(Piece::White, 100);
    // auto p2 = make_unique<MCTSPlayer>(Piece::Black, 100);
    string description = "Time to run (" + p1_type + " vs " + p2_type + 
        ") on (" + to_string(n) + " x " + to_string(n) + ") board: ";
    Game g(make_board("Hex", n)); 
    for (auto i = 0; i != 10; ++i) {
        timeit(description, &g, &Game::play, p1.get(), p2.get());
    }
}
