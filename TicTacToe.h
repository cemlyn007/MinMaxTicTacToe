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
    // I want:
    // * All game specific logic
    // * Scoring
    // * GameState

public:

    enum Score {
        O = -1, DRAW = 0, X = 1
    };

    enum GameState {
        RUNNING, FINISHED
    };

    int m, n, k;
    const Player PLAYER_MAX, PLAYER_MIN;
    Board board;

    TicTacToe(int m, int n, int k, Player player1, Player player2);

    GameState endTest(Board::Marker marker);

    bool checkVertical(int marker);

    bool checkHoriz(int marker);

    bool checkDiag(Board::Marker marker, int direction);

    bool checkWin(Board::Marker marker);

    bool hasNoBlanks();

    std::vector<std::tuple<int, int>> getOptions();


    std::tuple<int, int> getUserInput();

    virtual void play();

    void showBoard();

    Score getScore(Board::Marker marker);
};


#endif //MINIMAXTICTACTOE_TICTACTOE_H
