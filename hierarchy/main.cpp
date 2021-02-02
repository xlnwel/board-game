#include <iostream>
#include <utility>
#include <array>

#include "minmax_player.hpp"
#include "alphabeta_player.hpp"
#include "game.hpp"
#include "hex_board.hpp"
#include "state.hpp"

using namespace std;
using namespace game;

int main() {
    size_t n;
    cout << "Board size:\n";
    cin >> n;
    
    HexBoard hex(n);
    Game game(hex);
    AlphaBetaPlayer p1(Piece::White);
    AlphaBetaPlayer p2(Piece::Black);
    play(game, &p1, &p2);
}