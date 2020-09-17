//
// Created by cemlyn on 01/07/2020.
//

#include <iostream>

#include "Player.h"
#include "MinimaxTicTacToe.h"

int main() {
    std::cout << "Beginning" << std::endl;

    Player player1("Cemlyn", Board::X);
    player1.printInfo();

    Player player2("Bot", Board::O);
    player2.printInfo();

    MinimaxTicTacToe game(4,4,4, player1, player2);
    game.play();

    std::cout << "Finished" << std::endl;
}
