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

    explicit Player(std::string player_name="Player", char player_marker='!') {
        name = std::move(player_name);
        marker = player_marker;

    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] char get_marker() const {
        return marker;
    }

    void print_info(){
        std::cout << "Player name: " << name << " Marker: " << marker << std::endl;
    }

};


#endif //MINIMAXTICTACTOE_PLAYER_H
