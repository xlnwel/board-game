#include <iostream>
#include <utility>
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
    
    Game g(make_board("Hex", n)); 
    AlphaBetaPlayer p1(Piece::White);
    AlphaBetaPlayer p2(Piece::Black);
    g.play(&p1, &p2);
}