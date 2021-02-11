#include <iostream>
#include <string>

#include "basics.hpp"

using namespace std;
using namespace game;


Piece game::next_piece(Piece p) {
    switch (p) {
        case Piece::Blank:
        case Piece::Black: return Piece::White;
        case Piece::White: return Piece::Black;
    }
}
string game::get_piece_color(Piece p) {
    switch (p) {
        case Piece::Blank: return "None";
        case Piece::White: return "White";
        case Piece::Black: return "Black";
    }
}
