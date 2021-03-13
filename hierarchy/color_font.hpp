#ifndef GAME_COLOR_FONT_H_
#define GAME_COLOR_FONT_H_

#include <string>


namespace font {
    static constexpr std::string_view RESET("\033[0m");
    static constexpr std::string_view BLACK("\033[30m");
    static constexpr std::string_view RED("\033[31m");
    static constexpr std::string_view GREEN("\033[32m");
    static constexpr std::string_view YELLOW("\033[33m");
    static constexpr std::string_view BLUE("\033[34m");
    static constexpr std::string_view magenta("\033[35m");
    static constexpr std::string_view CYAN("\033[36m");
    static constexpr std::string_view WHITE("\033[37m");
}

#endif
