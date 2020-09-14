//
// Created by cemlyn on 01/07/2020.
//

#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include "Player.h"
#include "Board.h"

#ifndef MINIMAXTICTACTOE_TICTACTOE_H
#define MINIMAXTICTACTOE_TICTACTOE_H


class TicTacToe {
public:

    int m;
    int n;
    int k;
    Player max;
    Player min;
    Board board;

    TicTacToe(int m, int n, int k, Player player1, Player player2);

    int end_test(char marker);

    bool check_verts(int marker);

    bool check_horiz(int marker);

    bool check_diag(int marker, int direction);

    bool check_win(char marker);

    static std::tuple<int, int> get_user_input();

    void play();
};


#endif //MINIMAXTICTACTOE_TICTACTOE_H
