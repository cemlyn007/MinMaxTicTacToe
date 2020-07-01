//
// Created by cemlyn on 01/07/2020.
//

#include <iostream>

#include "Player.h"
#include "TicTacToe.h"

int main() {
    std::cout << "Beginning" << std::endl;

    Player player1("Cemlyn", 'X');
    player1.print_info();

    Player player2("Bot", 'O');
    player2.print_info();


    TicTacToe game(4, 5, 4, player1, player2);
    game.play();

    std::cout << "Finished" << std::endl;
}
