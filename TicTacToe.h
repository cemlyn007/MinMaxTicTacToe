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
    Player PLAYER_MAX;
    Player PLAYER_MIN;
    Board board;

    TicTacToe(int m, int n, int k, Player player1, Player player2);

    int endTest(char marker);

    bool checkVertical(int marker);

    bool checkHoriz(int marker);

    bool checkDiag(int marker, int direction);

    bool checkWin(char marker);

    std::tuple<int, int> getUserInput();

    void play();

    void showBoard();
};


#endif //MINIMAXTICTACTOE_TICTACTOE_H
