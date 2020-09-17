//
// Created by cemlyn on 14/09/2020.
//

#ifndef MINIMAXTICTACTOE_BOARD_H
#define MINIMAXTICTACTOE_BOARD_H

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>
#include <iostream>


class Board {
    // I Want this Class to:
    // * Screen Settings
    // * Print Board
    // * Board functionality

    // No game specific functionality here. This is just a board!

    // TODO:
    // * Move hasNoBlanks to TicTacToe


public:

    enum ScreenSetting {
        CONSOLE = -1, OFF, ON
    };
    enum Marker {
        O = -1, BLANK, X
    };

    enum MarkerChars{
        char_O = 'O', char_BLANK='_', char_X = 'X'
    };

    struct Mouse {
        int x = -1, y = -1;
    };

    Mouse mouse;
    const int M;
    const int N;
    const int WINDOWSIZE;
    ScreenSetting screen;
    cv::Mat image;
    std::vector<int> x_points;
    std::vector<int> y_points;
    const char WINDOWNAME[10];
    int MARKER_SIZE[2];
    std::vector<std::vector<Board::Marker>> board;


    Board(int n_rows, int n_cols, int window_size);

    void initialiseGridPoints();

    void resetImage();

    void showBoard();

    void populateCells();

    void drawBoard();

    void drawGrid();

    void drawLine(cv::Point start, cv::Point end, cv::Scalar color);

    void drawNought(int i, int j);

    void drawCross(int i, int j);

    void initialiseMarkerSize();

    static void callBackFunc(int event, int x, int y, int flags, void *userdata);

    static std::vector<std::vector<Board::Marker>> createBoardArray(int row_length, int column_width);

    std::tuple<int, int> getCell(int mouse_x, int mouse_y);

    std::tuple<int, int> getMousePosition();


    void printBoard();

    void markBoard(int i, int j, Marker marker);

    void markBoard(std::tuple<int, int> coord, Marker marker);

    void unmarkBoard(int i, int j);

    void unmarkBoard(std::tuple<int, int> coord);

    static void printMove(int i, int j);


    void resetMouse();

    char markerToChar(Marker marker);


};


#endif //MINIMAXTICTACTOE_BOARD_H
