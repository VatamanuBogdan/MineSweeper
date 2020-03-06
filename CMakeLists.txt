cmake_minimum_required(VERSION 3.15)
project(MineSweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(MineSweeper main.cpp MineSweeper.cpp Map.cpp Map.cpp MineCell.cpp)

include_directories(Headers)