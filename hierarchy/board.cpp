#include <algorithm>
#include <iterator>
#include <random>
#include <unordered_map>

#include "board.hpp"
#include "hex_board.hpp"

using namespace std;
using namespace game;


RhombusBoard::RhombusBoard(std::size_t nn): n(nn), board(std::vector<Piece>(n*n, Piece::Blank)) {}

vector<Point> RhombusBoard::get_valid_moves() const {
    vector<Point> valid_moves;
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t j = 0; j != n; ++j) {
            if (is_xy_valid(i, j))
                valid_moves.emplace_back(i, j);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(valid_moves.begin(), valid_moves.end(), g);
    return valid_moves;
}

bool RhombusBoard::reset(Point p) {
    std::size_t i = p.first, j = p.second;
    if (!is_xy_on_board(i, j))
        return false;
    board[xy2idx(i, j)] = Piece::Blank;
    return true;
}

bool RhombusBoard::move(Point p, Piece piece) {
    std::size_t i = p.first, j = p.second;
    if (!is_xy_on_board(i, j) || !is_xy_valid(i, j))
        return false;
    board[xy2idx(i, j)] = piece;
    return true;
}

ostream& operator<<(ostream& os, const Board& board) {
    board.display(os);
    return os;
}

unique_ptr<Board> game::make_board(const string& type, int n) {
    enum class BoardType {Hex};
    unordered_map<string_view, BoardType> type_map{
        {"Hex", BoardType::Hex},
    };
    switch (type_map[type]) {
        case BoardType::Hex: return unique_ptr<Board>(new HexBoard(n));
    }
}
