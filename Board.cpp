//
// Created by cemlyn on 14/09/2020.
//

#include <vector>
#include "Board.h"
#include <iostream>

using namespace cv;

const Scalar WHITE(255, 255, 255);


Board::Board(int n_rows, int n_cols, int window_size) :
        M(n_rows), N(n_cols), WINDOWSIZE(window_size),
        image(Mat::zeros(window_size, window_size, CV_8UC3)), WINDOWNAME("TicTacToe") {
    board = createBoardArray(M, N);

    if (window_size > 0) {
        screen = ON;
        initialiseMarkerSize();
        initialiseGridPoints();
    } else if (window_size == 0) {
        screen = CONSOLE;
    } else {
        screen = OFF;
    }
}


std::vector<std::vector<Board::Marker>> Board::createBoardArray(int row_length, int column_width) {
    std::vector<std::vector<Board::Marker>> new_board;
    for (int i = 0; i < row_length; i++) {
        std::vector<Board::Marker> temp(column_width, BLANK);
        new_board.push_back(temp);
    }
    return new_board;
}


void Board::printBoard() {
    std::cout << "Printing board" << std::endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << markerToChar(board[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Board::markBoard(int i, int j, Marker marker) {
    if (board[i][j] == BLANK) {
        board[i][j] = marker;
    } else {
        printMove(i, j);
        throw; // Wanted to mark somewhere that is already marked... (mistake was made)}

    }
}

void Board::unmarkBoard(int i, int j) {
    board[i][j] = BLANK;
}


void Board::drawGrid() {
    Point p1, p2;
    p1.x = 0;
    p2.x = WINDOWSIZE;
    for (int i = 0; i < N + 1; ++i) {
        p1.y = y_points[i];
        p2.y = y_points[i];
        drawLine(p1, p2, WHITE);
    }
    p1.y = 0;
    p2.y = WINDOWSIZE;
    for (int i = 0; i < M + 1; ++i) {
        p1.x = x_points[i];
        p2.x = x_points[i];
        drawLine(p1, p2, WHITE);
    }
}

void Board::initialiseGridPoints() {
    x_points.resize(M + 1);
    for (int i = 0; i < M + 1; ++i) { x_points[i] = std::round((i * WINDOWSIZE) / M); }
    y_points.resize(N + 1);
    for (int i = 0; i < N + 1; ++i) { y_points[i] = std::round((i * WINDOWSIZE) / N); }
}

void Board::drawLine(cv::Point start, cv::Point end, cv::Scalar color) {
    int thickness = 2;
    int lineType = LINE_8;
    line(image, start, end, color, thickness, lineType);
}

void Board::drawBoard() {
    resetImage();
    drawGrid();
    populateCells();
}

void Board::resetImage() {
    image = Mat::zeros(WINDOWSIZE, WINDOWSIZE, CV_8UC3);
}

void Board::showBoard() {
    namedWindow(WINDOWNAME, 0);
    setMouseCallback(WINDOWNAME, callBackFunc, NULL);
    imshow(WINDOWNAME, image);
    moveWindow(WINDOWNAME, 0, 200);
    waitKey(33);
}

void Board::initialiseMarkerSize() {
    MARKER_SIZE[0] = std::round(WINDOWSIZE / N);
    MARKER_SIZE[1] = std::round(WINDOWSIZE / M);
}

void Board::drawCross(int i, int j) {
    drawLine(Point(x_points[i], y_points[j]), Point(x_points[i + 1], y_points[j + 1]), WHITE);
    drawLine(Point(x_points[i], y_points[j + 1]), Point(x_points[i + 1], y_points[j]), WHITE);
}

void Board::drawNought(int i, int j) {
    int thickness = 2;
    int lineType = LINE_8;
    int centre_x = std::round((x_points[i] + x_points[i + 1]) / 2);
    int centre_y = std::round((y_points[j] + y_points[j + 1]) / 2);
    circle(image, Point(centre_x, centre_y), std::round(std::min(MARKER_SIZE[0], MARKER_SIZE[1]) / 2),
           WHITE, thickness, lineType);
}

void Board::callBackFunc(int event, int x, int y, int flags, void *userdata) {
    switch (event) {
        case EVENT_LBUTTONDOWN: {
//            std::vector<int> cell = getCell(x, y);
            std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
            Mouse *m = (Mouse *) userdata;
            m->x = x;
            m->y = y;
            break;
        }
        case EVENT_RBUTTONDOWN: {
            std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
            break;
        }
        default: {
            break;
        }
    }
}

void Board::populateCells() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            switch (board[i][j]) {
                case O:
                    drawNought(i, j);
                    break;
                case X:
                    drawCross(i, j);
                    break;
                case BLANK:
                    break;
            }
        }
    }

}

std::tuple<int, int> Board::getCell(int mouse_x, int mouse_y) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if ((x_points[i] < mouse_x) and (mouse_x < x_points[i + 1])
                and (y_points[j] < mouse_y) and (mouse_y < y_points[j + 1])) {
                return std::tuple<int, int>(i, j);
            }
        }
    }
}

std::tuple<int, int> Board::getMousePosition() {
    namedWindow(WINDOWNAME, 0);
    setMouseCallback(WINDOWNAME, callBackFunc, &mouse);
    waitKey(33);
    while (true) {
        imshow(WINDOWNAME, image);
        waitKey(60);
        if (mouse.x != -1 and mouse.y != -1) { break; }
    }
    std::tuple<int, int> mouse_position(mouse.x, mouse.y);
    resetMouse();
    return mouse_position;
}

void Board::resetMouse() {
    mouse.x = -1;
    mouse.y = -1;
}

char Board::markerToChar(Marker marker) {
    switch (marker) {
        case Marker::O:
            return MarkerChars::char_O;
        case Marker::BLANK:
            return MarkerChars::char_BLANK;
        case Marker::X:
            return MarkerChars::char_X;
    }
    return 0;
}

void Board::markBoard(std::tuple<int, int> coord, Board::Marker marker) {
    // TODO: markBoard should not be responsible for checking that the cell is indeed BLANK!
    int i = std::get<0>(coord);
    int j = std::get<1>(coord);
    if (board[i][j] == BLANK) {
        board[i][j] = marker;
    } else {
        printMove(i, j);
        throw; // Wanted to mark somewhere that is already marked... (mistake was made)}

    }
}

void Board::unmarkBoard(std::tuple<int, int> coord) {
    int i = std::get<0>(coord);
    int j = std::get<1>(coord);
    board[i][j] = BLANK;
}

void Board::printMove(int i, int j) {
    std::cout << "Move: (" << i << ", " << j << ")" << std::endl;
}



