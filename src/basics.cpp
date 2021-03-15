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
        case Piece::Blank: return "Blank";
        case Piece::White: return "White";
        case Piece::Black: return "Black";
    }
}

int game::compute_score(Result r) {
    switch (r) {
    case Result::Win: return 1;
    case Result::Loss: return -1;
    default: return 0;
    }
}

ostream& game::operator<<(ostream& os, Point p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

ostream& game::operator<<(ostream& os, Piece p) {
    os << get_piece_color(p);
    return os;
}

ostream& game::operator<<(ostream& os, Result p) {
    os << compute_score(p);
    return os;
}
