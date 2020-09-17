//
// Created by cemlyn on 01/07/2020.
//

#include <iostream>
#include <utility>
#include "Board.h"


#ifndef MINIMAXTICTACTOE_PLAYER_H
#define MINIMAXTICTACTOE_PLAYER_H


class Player {

public:
    std::string name;
    Board::Marker marker;
    Player(std::string player_name, Board::Marker player_marker);
    std::string getName() const;
    Board::Marker getMarker() const;
    void printInfo();
};


#endif //MINIMAXTICTACTOE_PLAYER_H
