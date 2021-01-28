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


std::vector<Point> HexBoard::get_adjacent_points(Point p, Piece piece) const {
    int i = get<0>(p), j = get<1>(p);
    std::vector<Point> ans;
    for (const auto& x: HexNeighbor) {
        auto m = i + get<0>(x), n = j + get<1>(x);
        Point p = std::make_pair(m, n);
        if (is_on_board(m, n) && get_piece(m, n) == piece) {
            ans.push_back(p);
        }
    }
    return ans;
}

// int main() {
//     HexBoard board(4);
//     board.display();
//     board.move(make_pair(0, 0), Piece::White);
//     board.move(make_pair(0, 1), Piece::Black);
//     board.display();
//     board.move(make_pair(1, 0), Piece::White);
//     board.move(make_pair(1, 2), Piece::White);
//     board.display();
//     board.move(make_pair(2, 0), Piece::White);
//     board.move(make_pair(2, 2), Piece::Black);
//     board.display();
//     board.move(make_pair(3, 0), Piece::White);
//     board.display();
// }