//
// Created by cemlyn on 02/07/2020.
//

#ifndef MINIMAXTICTACTOE_MINIMAXTICTACTOE_H
#define MINIMAXTICTACTOE_MINIMAXTICTACTOE_H


#include "Player.h"
#include "TicTacToe.h"

class MinimaxTicTacToe : public TicTacToe {

public:

    MinimaxTicTacToe(int m, int n, int k, Player player1, Player player2);

    std::tuple<int, int> getBestMove(const Player &curr_player, const Player &next_player);

    TicTacToe::Score getMiniMax(const Player &player, const Player &prev_player);

    std::tuple<int, int> getUserInput(const Player &curr_player, const Player &next_player);

    void play() override;

};


#endif //MINIMAXTICTACTOE_MINIMAXTICTACTOE_H
