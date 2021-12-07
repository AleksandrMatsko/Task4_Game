#include "Player.h"

namespace {
    void ToLower(std::string& str) {
        for (int i = 0; i < str.size(); i++) {
            str[i] = char(std::tolower(str[i]));
        }
    }

    std::string GetAction(std::istream& in, std::ostream& out, bool shoot_possible) {
        out << "Please choose one action:" << std::endl;
        std::string action;
        while (true) {
            in >> action;
            ToLower(action);
            if (action == "move") {
                return action;
            }
            if (action == "shoot" && shoot_possible) {
                return action;
            }
            out << "Please choose one action:" << std::endl;
        }
    }

    Direction GetDirection(std::istream& in, std::ostream& out) {
        out << "Please choose 1 of 4 directions (up, down, left, right):" << std::endl;
        std::string direction;
        while (true) {
            in >> direction;
            ToLower(direction);
            if (direction == "up") {
                return Direction::UP;
            }
            else if (direction == "down") {
                return Direction::DOWN;
            }
            else if (direction == "left") {
                return Direction::LEFT;
            }
            else if (direction == "right") {
                return Direction::RIGHT;
            }
            out << "Please choose 1 of 4 directions (up, down, left, right):" << std::endl;
        }
    }
}

Player::Player(const std::pair<int, int>& start_pos, int width, int height) {
    _pos = start_pos;
    _open_field = std::make_shared<OpenField>(start_pos, width, height);
    _skip_turn = false;
    _can_shoot = true;
}

std::pair<std::string, Direction> Player::chooseAction(std::istream& in, std::ostream& out) {
    if (_skip_turn) {
        //exception
    }
    out << "You can do these actions:" << std::endl;
    out << "- move" << std::endl;
    if (_can_shoot) {
        out << "- shoot" << std::endl;
    }
    auto action = GetAction(in, out, _can_shoot);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto direction = GetDirection(in, out);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_pair(action, direction);
}

void Player::setPosition(const std::pair<int, int>& new_pos) {
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