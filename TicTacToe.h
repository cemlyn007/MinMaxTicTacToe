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

enum Score {
    O = -1, DRAW = 0, X = 1
};

enum GameState {
    RUNNING, FINISHED
};


class TicTacToe {
    // I want:
    // * All game specific logic
    // * Scoring
    // * GameState



public:


    int m, n, k;
    const Player PLAYER_MAX, PLAYER_MIN;
    Board main_board;

    TicTacToe(int m, int n, int k, Player player1, Player player2);

    // Normal functionality

    GameState endTest(Board::Marker marker);

    Score getScore(Board::Marker marker);

    static Score getWorstCaseScore(Board::Marker marker);

    bool checkVertical(Board::Marker &marker);

    bool checkHoriz(Board::Marker &marker);

    bool checkDiag(Board::Marker &marker, int direction);

    bool checkWin(Board::Marker &marker);

    bool hasNoBlanks();

    std::vector<std::tuple<int, int>> getOptions();

    // Threading

    std::vector<std::tuple<int, int>> getOptions(Board board);

    GameState endTest(Board &board, Board::Marker marker);

    Score getScore(Board &board, Board::Marker marker);

    bool checkVertical(Board &board, Board::Marker &marker);

    bool checkHoriz(Board &board, Board::Marker &marker);

    bool checkDiag(Board &board, Board::Marker &marker, int direction);

    bool checkWin(Board &board, Board::Marker &marker);

    bool hasNoBlanks(Board &board);

    Board getMainBoard();


    // Adjustable functions

    virtual void play();

    std::tuple<int, int> getUserInput();

    void showBoard();


};


#endif //MINIMAXTICTACTOE_TICTACTOE_H
