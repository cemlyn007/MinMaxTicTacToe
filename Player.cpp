//
// Created by cemlyn on 14/09/2020.
//

#include "Player.h"
#include <iostream>

Player::Player(std::string player_name, int player_marker) {
    name = std::move(player_name);
    marker = player_marker;
}

std::string Player::getName() {
    return Player::name;
}

int Player::getMarker() {
    return Player::marker;
}

void Player::printInfo() {
    std::cout << "Player name: " << Player::getName() << " Marker: " << Player::getMarker() << std::endl;
}
