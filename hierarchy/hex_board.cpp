#include <iostream>
#include <stack>
#include <string>
#include <utility>

#include "color_font.hpp"
#include "hex_board.hpp"

using namespace std;
using namespace game;


void HexBoard::display(std::ostream& os) const {
    auto n = get_board_size();
    for (auto i = 0; i != n; ++i) {
        os << std::string(i, ' ');
        for (auto j = 0; j != n; ++j) {
            auto x = get_xy_piece(i, j);
            switch (x) {
                case Piece::Blank: os << ". "; 
                    break;
                case Piece::White: os << font::WHITE << "x " << font::RESET; 
                    break;
                case Piece::Black: os << font::BLACK << "o " << font::RESET; 
                    break;
            }
        }
        os << '\n';
    }
}

Result HexBoard::result(Point point, Piece piece) const {
    // perform dfs to check if the current Piece won
    if (piece == Piece::Blank)
        return Result::Unknown;
    auto board = *this;
    auto n = get_board_size();

    bool topdown = piece == Piece::White;
    bool first = false, second = false;
    stack<Point> v;
    v.push(point);
    board.reset(point);
    while (!v.empty()) {
        auto p = v.top();
        v.pop();
        if (topdown) {
            if (p.first == 0)
                first = true;
            else if (p.first == n-1)
                second = true;
        }
        else {
            if (p.second == 0)
                first = true;
            else if (p.second == n-1)
                second = true;
        }
        auto ps = board.get_adjacent_points(p, piece);
        for (auto x: ps) {
            v.push(x);
            board.reset(x);
        }
        if (first && second) {
            return Result::Win;
        }
    }
    auto result = Result::Unknown;
    return result;
}

vector<Point> HexBoard::get_adjacent_points(
        Point point, Piece piece) const {
    std::size_t i = point.first, j = point.second;
    std::size_t n = get_board_size();
    std::vector<Point> ans;
    for (const auto& s: HexNeighbor) {
        std::size_t x = i + s.first, y = j + s.second;
        if (is_xy_on_board(x, y) && get_xy_piece(x, y) == piece) {
            ans.push_back(make_pair(x, y));
        }
    }
    return ans;
}
