#include <unordered_map>

#include "board.hpp"
#include "hex_board.hpp"

using namespace std;
using namespace game;


RhombusBoard::RhombusBoard(std::size_t nn): n(nn), board(std::vector<Piece>(n*n, Piece::Blank)) {}

unordered_set<Point, PointHash> RhombusBoard::get_valid_moves() const {
    unordered_set<Point, PointHash> valid_moves;
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t j = 0; j != n; ++j) {
            if (is_xy_valid(i, j))
                valid_moves.emplace(i, j);
        }
    }
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
