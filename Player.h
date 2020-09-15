//
// Created by cemlyn on 01/07/2020.
//

#include <iostream>
#include <utility>


#ifndef MINIMAXTICTACTOE_PLAYER_H
#define MINIMAXTICTACTOE_PLAYER_H


class Player {

public:
    std::string name;
    char marker;
    Player(std::string player_name, int player_marker);
    std::string getName();
    int getMarker();
    void printInfo();
};


#endif //MINIMAXTICTACTOE_PLAYER_H
