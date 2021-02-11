#include <iostream>
#include <utility>
#include <array>

#include "minmax_player.hpp"
#include "game.hpp"
#include "hex_board.hpp"

using namespace std;
using namespace game;

std::size_t main() {
    HexBoard board(4);
    State<HexBoard> state(board);
    Game<HexBoard> game;
    MinMaxPlayer<HexBoard> player1(Piece::White);
    MinMaxPlayer<HexBoard> player2(Piece::Black);
    Point move;
    while (state.get_utility() == 0) {
        auto piece = state.to_move();
        switch (piece) {
            case Piece::White: move = player1(game, state); break;
            case Piece::Black: move = player2(game, state); break;
            case Piece::Blank: assert(false);
        }
        state = game.result(state, move, piece);
        state.display();
    }
}