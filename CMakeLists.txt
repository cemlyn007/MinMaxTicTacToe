cmake_minimum_required(VERSION 3.16)
project(MiniMaxTicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(MiniMaxTicTacToe Player.cpp Player.h main.cpp TicTacToe.cpp TicTacToe.h MiniMax.cpp MiniMax.h Board.cpp Board.h)