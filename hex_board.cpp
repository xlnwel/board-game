#include <iostream>
#include <string>
#include <utility>

#include "hex_board.hpp"

using namespace std;
using namespace game;


HexBoard::HexBoard(int nn): Board(nn) {}

HexBoard::HexBoard(const HexBoard& other): Board(other) {}

HexBoard::HexBoard(HexBoard&& other): Board(std::move(other)) {}

HexBoard& HexBoard::operator=(const HexBoard& rhs) {
    if (this != &rhs) {
        Board::operator=(rhs);
    }
    return *this;
}

HexBoard& HexBoard::operator=(HexBoard&& rhs) {
    if (this != &rhs) {
        Board::operator=(std::move(rhs));
    }
    return *this;
}
        
void HexBoard::display() const {
    static constexpr char RESET[] = "\033[0m";
    static constexpr char RED[] = "\033[31m";
    static constexpr char BLUE[] = "\033[34m";
    auto n = get_board_size();
    for (auto i = 0; i != n; ++i) {
        std::cout << std::string(i, ' ');
        for (auto j = 0; j != n; ++j) {
            auto x = Board::get_piece(i, j);
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

vector<Point> game::HexBoard::get_adjacent_points(Point point, Piece piece) const {
    int i = point.first, j = point.second;
    int n = get_board_size();
    std::vector<Point> ans;
    for (const auto& s: HexNeighbor) {
        int x = i + s.first, y = j + s.second;
        if (is_on_board(x, y) && get_piece(x, y) == piece) {
            ans.push_back(make_pair(x, y));
        }
    }
    return ans;
}
