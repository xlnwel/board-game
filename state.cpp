#include <iostream>

#include "basics.hpp"
#include "hex_board.hpp"
#include "hex_state.hpp"


using namespace std;
using namespace game;

int main() {
    HexBoard hex0(4);
    HexBoard hex(5);
    hex = std::move(hex0);
    Piece piece = Piece::White;
    State<HexBoard> s(hex, piece);
    const auto& board = s.get_board();
    auto moves = s.get_valid_moves();
    for (auto p: moves) {
        auto succ = s.update_board(p, piece);
        cout << get_piece_color(piece) << " update at (" << p.first << ", "
             << p.second << ")" << std::endl;
        board.display();
        if (s.is_over()) {
            cout << "Winner: " << get_piece_color(piece) << endl;
            break;
        }
        piece = s.to_move();
    }
}