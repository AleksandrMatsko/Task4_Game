#include "Player.h"

Player::Player(const std::pair<int, int> start_pos, const int width, const int height) {
    _pos = start_pos;
    _open_field = std::make_shared<OpenField>(start_pos, width, height);
    _skip_turn = false;
    _can_shoot = true;
}

void Player::setPosition(const std::pair<int, int> &new_pos) {
    _pos = new_pos;
}

std::pair<int, int> Player::getPosition() {
    return _pos;
}

bool Player::isSkip() {
    return _skip_turn;
}

bool Player::canShoot() {
    return _can_shoot;
}

void Player::setShootMode(bool mode) {
    _can_shoot = mode;
}

void Player::setSkipMode(bool mode) {
    _skip_turn = mode;
}

std::shared_ptr<OpenField> Player::getOpenedField() {
    return _open_field;
}