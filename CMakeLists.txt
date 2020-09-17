cmake_minimum_required(VERSION 3.16)
project(MiniMaxTicTacToe)

set(OpenCV_DIR "/mnt/UHDD/Programming/Cxx/sources/opencv/build")

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 20)

add_executable(MiniMaxTicTacToe Player.cpp Player.h main.cpp TicTacToe.cpp TicTacToe.h MinimaxTicTacToe.cpp MinimaxTicTacToe.h Board.cpp Board.h)

target_link_libraries( MiniMaxTicTacToe ${OpenCV_LIBS} )