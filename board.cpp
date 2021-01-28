#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;
using namespace game;


std::string get_piece_color(Piece p) {
    switch (p) {
        case Piece::Blank: return "None";
        case Piece::White: return "White";
        case Piece::Black: return "Black";
    }
}

Board::Board(int nn): n(nn), board(nn, vector<Piece>(nn, Piece::Blank)) {}

Board::Board(const Board& other): board(other.board) {}

Board::Board(Board&& other): board(std::move(other.board)) {}

Board& Board::operator=(const Board& rhs) {
    if (this != &rhs) {
        n = rhs.n;
        board = rhs.board;
    }
    return *this;
}

Board& Board::operator=(Board&& rhs) {
    if (this != &rhs) {
        n = rhs.n;
        board = std::move(rhs.board);
    }
    return *this;
}

bool Board::move(Point p, Piece piece) {
    int i = get<0>(p), j = get<1>(p);
    if (!is_on_board(i, j) || !is_valid(i, j))
        return false;
    board[i][j] = piece;
    return true;
}

vector<Point> Board::get_valid_moves() const {
    vector<Point> moves;
    for (auto i = 0; i != n; ++i) {
        for (auto j = 0; j != n; ++j) {
            if (is_valid(i, j))
                moves.push_back(make_pair(i, j));
        }
    }
}
