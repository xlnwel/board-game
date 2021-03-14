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

Result HexBoard::result(Point move, Piece piece) const {
    // perform dfs to check if the current Piece won
    if (piece == Piece::Blank)
        return Result::Unknown;
    auto board = *this;
    auto n = get_board_size();

    bool topdown = piece == Piece::White;
    bool first = false, second = false;
    stack<Point> v;
    v.push(move);
    board.reset(move);
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

double HexBoard::compute_utility(Piece piece) const {
    auto board = *this;
    auto n = get_board_size();
    int top = n-1, down = 0;
    int left = n-1, right = 0;
    stack<Point> v;
    auto size = n * n;
    for (auto i = 0; i != size; ++i) {
        Point m{i / n, i % n};
        auto piece = board.get_piece(m);
        if (piece == Piece::Blank)
            continue;
        if (piece == Piece::White) {
            auto [t, d] = search_top_down(board, m);
            if (d - t > down - top) {
                top = t;
                down = d;
            }
        }
        else {
            auto [l, r] = search_left_right(board, m);
            if (r - l > right - left) {
                left = l;
                right = r;
            }
        }
    }
    auto white_score = static_cast<double>(down - top + 1) / n;
    auto black_score = static_cast<double>(right - left + 1) / n;
    // display();
    // cout << piece << down - top + 1 << " " << right - left + 1 << endl;
    // assert(false);
    return piece == Piece::White? white_score - black_score: black_score - white_score;
}

vector<Point> HexBoard::get_adjacent_points(
        Point move, Piece piece) const {
    auto i = move.first, j = move.second;
    auto n = get_board_size();
    std::vector<Point> ans;
    for (const auto& s: HexNeighbor) {
        auto x = i + s.first, y = j + s.second;
        if (is_xy_on_board(x, y) && get_xy_piece(x, y) == piece) {
            ans.emplace_back(x, y);
        }
    }
    return ans;
}

std::pair<int, int> HexBoard::search_top_down(HexBoard& board, Point move) const {
    assert(board.get_piece(move) == Piece::White);
    stack<Point> v;
    v.push(move);
    board.reset(move);
    int top = get_board_size();
    int down = 0;
    while (!v.empty()) {
        auto p = v.top();
        v.pop();
        if (p.first < top)
            top = p.first;
        if (p.first > down)
            down = p.first;
        auto ps = board.get_adjacent_points(p, Piece::White);
        for (auto x: ps) {
            v.push(x);
            board.reset(x);
        }
    }
    return {top, down};
}

std::pair<int, int> HexBoard::search_left_right(HexBoard& board, Point move) const {
    assert(board.get_piece(move) == Piece::Black);
    stack<Point> v;
    v.push(move);
    board.reset(move);
    int left = get_board_size();
    int right = 0;
    while (!v.empty()) {
        auto p = v.top();
        v.pop();
        if (p.second < left)
            left = p.second;
        if (p.second > right)
            right = p.second;
        auto ps = board.get_adjacent_points(p, Piece::Black);
        for (auto x: ps) {
            v.push(x);
            board.reset(x);
        }
    }
    return {left, right};
}
