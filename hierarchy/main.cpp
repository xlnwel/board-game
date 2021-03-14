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
#include "minmax_player.hpp"
#include "mcts_player.hpp"

#include "board.hpp"
#include "game.hpp"
#include "state.hpp"
#include "utils.hpp"


using namespace game;
using namespace std;
using namespace utility;

string ask_for_player_type(int player_idx) {
    string pt;
    cout << "Select player" << player_idx << "(AlphaBeta MCTS MinMax): ";
    cin >> pt;
    transform(pt.begin(), pt.end(), pt.begin(), ::toupper);
    return pt;
}

int ask_for_num_mcts_simulations(const string& p, int player_idx) {
    if (p != "MCTS")
        return 0;
    cout << "The number of simulations performed by player" << player_idx << ": ";
    int n;
    cin >> n;
    return n;
}

unique_ptr<Player> create_player(const string& s, Piece p, int n) {
    if (s == "ALPHABETA")
        return make_unique<AlphaBetaPlayer>(p);
    if (s == "MCTS")
        return make_unique<MCTSPlayer>(p, n);
    if (s == "MINMAX")
        return make_unique<MinMaxPlayer>(p);
    throw invalid_argument("Invalid player type: " + s);
}

int main() {
    // cout << "Board size: ";
    // size_t n;
    // cin >> n;
    // string p1_type = ask_for_player_type(1);
    // string p2_type = ask_for_player_type(2);
    // int n1 = ask_for_num_mcts_simulations(p1_type, 1);
    // int n2 = ask_for_num_mcts_simulations(p2_type, 2);

    // auto p1 = create_player(p1_type, Piece::White, n1);
    // auto p2 = create_player(p2_type, Piece::Black, n2);
    int n = 3;
    string p1_type = "ALPHABETA";
    string p2_type = "ALPHABETA";
    auto p1 = make_unique<MinMaxPlayer>(Piece::White);
    auto p2 = make_unique<MinMaxPlayer>(Piece::Black);
    string description = "Time to run (" + p1_type + " vs " + p2_type + 
        ") on (" + to_string(n) + " x " + to_string(n) + ") board: ";
    Game g(make_board("Hex", n)); 
    for (auto i = 0; i != 10; ++i) {
        timeit(description, &g, &Game::play, p1.get(), p2.get());
    }
}
