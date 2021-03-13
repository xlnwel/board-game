#include <iostream>
#include <iomanip>
#include <ios>
#include <utility>
#include <chrono>
#include <array>

#include "minmax_player.hpp"
#include "alphabeta_player.hpp"
#include "game.hpp"
#include "board.hpp"
#include "state.hpp"

using namespace std;
using namespace game;

int main() {
    size_t n;
    cout << "Board size:\n";
    cin >> n;
    
    auto start = std::chrono::steady_clock::now();
    Game g(make_board("Hex", n)); 
    AlphaBetaPlayer p1(Piece::White);
    AlphaBetaPlayer p2(Piece::Black);
    g.play(&p1, &p2);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << std::fixed << std::setprecision(5) << std::left;
    std::cout << "Time to run " << "AlphaBetaPlayer" << " for (" 
        << n << " x " << n << ") board: " << diff.count() << "s\n";
}
