//
// Created by cemlyn on 14/09/2020.
//

#include <vector>
#include "Board.h"
#include <iostream>


Board::Board(int num_rows, int num_cols) {
    m = num_rows;
    n = num_cols;
    board = Board::create_board(m, n);
}

std::vector<std::vector<char>> Board::create_board(int row_length, int column_width) {
    std::vector<std::vector<char>> new_board;
    for (int i = 0; i < row_length; i++) {
        std::vector<char> temp(column_width, Board::BLANK);
        new_board.push_back(temp);
    }
    return new_board;
}


void Board::print_board() {
    std::cout << "Printing board" << std::endl;
    for (int i = 0; i < Board::m; i++) {
        for (int j = 0; j < Board::n; j++) {
            std::cout << Board::board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::mark_board(int i, int j, char marker) {
    if (Board::board[i][j] == Board::BLANK) {
        Board::board[i][j] = marker;
    } else {
        throw; // Wanted to mark somewhere that is already marked... (mistake was made)
    }

}

void Board::unmark_board(int i, int j) {
    Board::board[i][j] = Board::BLANK;
}


bool Board::no_blanks() {
    for (int i = 0; i < Board::m; i++) {
        for (int j = 0; j < Board::n; j++) {
            if (Board::board[i][j] == Board::BLANK) {
                return false;
            }
        }
    }
    return true;
}