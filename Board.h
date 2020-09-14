//
// Created by cemlyn on 14/09/2020.
//

#ifndef MINIMAXTICTACTOE_BOARD_H
#define MINIMAXTICTACTOE_BOARD_H


class Board {

public:

    const char BLANK = '_';
    int m;
    int n;
    std::vector<std::vector<char>> board;

    Board(int num_rows, int num_cols);
    Board();

    std::vector<std::vector<char>> create_board(int row_length, int column_width);

    void print_board();
    void mark_board(int i, int j, char marker);
    void unmark_board(int i, int j);
    bool no_blanks();


};


#endif //MINIMAXTICTACTOE_BOARD_H
