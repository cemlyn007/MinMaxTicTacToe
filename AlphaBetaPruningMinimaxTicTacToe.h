//
// Created by cemlyn on 18/09/2020.
//

#ifndef MINIMAXTICTACTOE_ALPHABETAPRUNINGMINIMAXTICTACTOE_H
#define MINIMAXTICTACTOE_ALPHABETAPRUNINGMINIMAXTICTACTOE_H


#include "Player.h"
#include "TicTacToe.h"

class AlphaBetaPruningMinimaxTicTacToe : private TicTacToe {
private:
    Score getMiniMaxOfOption(std::tuple<int, int> option, const Player &curr_player, const Player &next_player);

public:

    AlphaBetaPruningMinimaxTicTacToe(int m, int n, int k, Player player1, Player player2);

    std::tuple<int, int> getBestMove(const Player &curr_player, const Player &next_player);

    Score getMiniMax(Board &board, const Player &player, const Player &prev_player, int alpha, int beta);

    std::tuple<int, int> getUserInput(const Player &curr_player, const Player &next_player);

    void play() override;

};


#endif //MINIMAXTICTACTOE_ALPHABETAPRUNINGMINIMAXTICTACTOE_H
