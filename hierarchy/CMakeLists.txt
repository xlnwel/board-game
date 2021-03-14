cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Game)

add_executable(Game main.cpp alphabeta_player.cpp minmax_player.cpp mcts_player.cpp board.cpp hex_board.cpp state.cpp game.cpp basics.cpp)
