//
// Created by cemlyn on 14/09/2020.
//

#include "Player.h"
#include <iostream>

Player::Player(std::string player_name, char player_marker) {
    name = std::move(player_name);
    marker = player_marker;
}

std::string Player::get_name() {
    return Player::name;
}

char Player::get_marker() {
    return Player::marker;
}

void Player::print_info() {
    std::cout << "Player name: " << Player::get_name() << " Marker: " << Player::get_marker() << std::endl;
}
