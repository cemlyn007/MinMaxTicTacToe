cmake_minimum_required(VERSION 3.16)
project(MiniMaxTicTacToe)

set(OpenCV_DIR "/mnt/UHDD/Programming/Cxx/sources/opencv/build")

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(MiniMaxTicTacToe
        Player.cpp Player.h main.cpp
        TicTacToe.cpp TicTacToe.h
        Board.cpp Board.h
        AlphaBetaPruningMinimaxTicTacToe.cpp AlphaBetaPruningMinimaxTicTacToe.h
        )

target_link_libraries( MiniMaxTicTacToe ${OpenCV_LIBS} )