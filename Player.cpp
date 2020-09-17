//
// Created by cemlyn on 14/09/2020.
//

#include "Player.h"
#include <iostream>
#include <utility>

Player::Player(std::string player_name, Board::Marker player_marker) : name(player_name), marker(player_marker) {
}

std::string Player::getName() const {
    return Player::name;
}

Board::Marker Player::getMarker() const {
    return Player::marker;
}

void Player::printInfo() {
    std::cout << "Player name: " << Player::getName() << " Marker: " << Player::getMarker() << std::endl;
}
