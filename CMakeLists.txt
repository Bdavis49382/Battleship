cmake_minimum_required(VERSION 3.23)
project(battleship)

set(CMAKE_CXX_STANDARD 14)

add_executable(battleship main.cpp Player.cpp Player.h)
