#include <iostream>
#include <string>
#include <utility>

#include "hex_board.hpp"

using namespace std;
using namespace game;


void HexBoard::display() const {
    static constexpr char RESET[] = "\033[0m";
    static constexpr char RED[] = "\033[31m";
    static constexpr char BLUE[] = "\033[34m";
    auto n = get_board_size();
    for (auto i = 0; i != n; ++i) {
        std::cout << std::string(i, ' ');
        for (auto j = 0; j != n; ++j) {
            auto x = get_piece(i, j);
            switch (x) {
                case Piece::Blank: std::cout << ". "; 
                    break;
                case Piece::White: std::cout << RED << "x " << RESET; 
                    break;
                case Piece::Black: std::cout << BLUE << "o " << RESET; 
                    break;
            }
        }
        std::cout << std::endl;
    }
}

vector<Point> HexBoard::get_adjacent_points(Point point, Piece piece) const {
    std::size_t i = point.first, j = point.second;
    std::size_t n = get_board_size();
    std::vector<Point> ans;
    for (const auto& s: HexNeighbor) {
        std::size_t x = i + s.first, y = j + s.second;
        if (is_on_board(x, y) && get_piece(x, y) == piece) {
            ans.push_back(make_pair(x, y));
        }
    }
    return ans;
}
