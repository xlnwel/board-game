cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Game)

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SRCS)
add_executable(game ${SRCS})
