#include "board.hpp"

using namespace std;
using namespace game;


Board::Board(int nn): n(nn), board(nn, vector<Piece>(nn, Piece::Blank)) {
    assert(n > 0);
}

Board::Board(const Board& other): n(other.n), board(other.board) {}

Board::Board(Board&& other): n(other.n), board(std::move(other.board)) {}

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

bool Board::reset(Point p) {
    int i = p.first, j = p.second;
    if (!is_on_board(i, j))
        return false;
    board[i][j] = Piece::Blank;
    return true;
}

bool Board::move(Point p, Piece piece) {
    int i = p.first, j = p.second;
    if (!is_on_board(i, j) || !is_valid(i, j))
        return false;
    board[i][j] = piece;
    return true;
}

unordered_set<Point, PointHash> Board::get_valid_moves() {
    unordered_set<Point, PointHash> valid_moves;
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (is_valid(i, j))
                valid_moves.emplace(i, j);
        }
    }
    return valid_moves;
}
