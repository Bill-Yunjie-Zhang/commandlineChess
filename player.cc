#include "player.h"

void Player::setId(int num) {
    id = num;
}

void Player::setColor(string str) {
    color = str;
}

void Player::setBot(bool isMachine) {
    isBot = isMachine;
}

int Player::getId() {
    return id;
}