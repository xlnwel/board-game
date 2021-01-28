#ifndef GAME_BASICS_H_
#define GAME_BASICS_H_

#include <string>
#include <utility>


namespace game {
    enum class Piece {Blank, White, Black};
    using Point = std::pair<int, int>;
    
    std::string get_piece_color(Piece p);
}

#endif
