cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Game)

AUX_SOURCE_DIRECTORY(src SRCS)
AUX_SOURCE_DIRECTORY(thread SRCS)
add_executable(game ${SRCS})
