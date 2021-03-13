#include <iostream>
#include <string>
#include <utility>

#include "hex_board.hpp"
#include "color_font.hpp"

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

bool HexBoard::is_over(Point point, Piece piece) const {
    // perform dfs to check if the current Piece won
    auto board = *this;
    auto n = get_board_size();

    bool topdown = piece == Piece::White;
    bool first = false, second = false;
    std::vector<Point> v{point};
    board.reset(point);
    while (!v.empty()) {
        auto p = v.back();
        v.pop_back();
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
            v.push_back(x);
            board.reset(x);
        }
        if (first && second) {
            return true;
        }
    }
    return false;
}

vector<Point> HexBoard::get_adjacent_points(Point point, Piece piece) const {
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
