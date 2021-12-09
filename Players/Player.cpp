#include "Player.h"

namespace StrModifier {
    void ToLower(std::string &str) {
        for (int i = 0; i < str.size(); i++) {
            str[i] = char(std::tolower(str[i]));
        }
    }
}

Direction operator!(Direction direction) {
    if (direction == Direction::UP) {
        return Direction::DOWN;
    }
    else if (direction == Direction::DOWN) {
        return Direction::UP;
    }
    else if(direction == Direction::RIGHT) {
        return Direction::LEFT;
    }
    else if(direction == Direction::LEFT) {
        return Direction::RIGHT;
    }
    else {
        return Direction::NONE;
    }
}

void printDirection(Direction direction, std::ostream& out) {
    if (direction == Direction::UP) {
        out << "UP";
    }
    else if (direction == Direction::DOWN) {
        out << "DOWN";
    }
    else if(direction == Direction::RIGHT) {
        out << "RIGHT";
    }
    else if(direction == Direction::LEFT) {
        out << "LEFT";
    }
    else {
        out << "NONE";
    }
}

namespace {
    std::string GetNameAction(std::istream& in, std::ostream& out, std::map<std::string, bool> possible_actions) {
        out << "Please choose one action:" << std::endl;
        std::string action;
        while (true) {
            in >> action;
            StrModifier::ToLower(action);
            if (possible_actions.find(action) != possible_actions.end()) {
                bool available = possible_actions[action];
                if (available) {
                    return action;
                }
            }
            out << "Please choose one action:" << std::endl;
        }
    }

    Direction GetDirection(std::istream& in, std::ostream& out) {
        out << "Please choose 1 of 4 directions (up, down, left, right):" << std::endl;
        std::string direction;
        while (true) {
            in >> direction;
            StrModifier::ToLower(direction);
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

Player::Player(const std::pair<int, int>& start_pos, int width, int height,
               const std::map<std::string, bool>& possible_actions) {
    _pos = start_pos;
    _open_field = std::make_shared<OpenField>(start_pos, width, height);
    _skip_turn = false;
    _possible_actions = possible_actions;
    _treasure_is_hold = false;
    _i_hold_treasure = false;
}

std::pair<std::string, Direction> Player::chooseAction(std::istream& in, std::ostream& out) {
    if (_skip_turn) {
        //exception
    }
    out << "You can do these actions:" << std::endl;
    for (auto & it: _possible_actions){
        if (it.second) {
            out << "- " << it.first << std::endl;
        }
    }
    auto action_name = GetNameAction(in, out, _possible_actions);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto direction = GetDirection(in, out);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_pair(action_name, direction);
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

void Player::setActionMode(const std::string &action, bool mode) {
    _possible_actions[action] = mode;
}

void Player::setSkipMode(bool mode) {
    _skip_turn = mode;
}

std::shared_ptr<OpenField> Player::getOpenedField() {
    return _open_field;
}

bool Player::isAvailable(const std::string& action) {
    return _possible_actions[action];
}

bool Player::isBot() {
    return false;
}

bool Player::isTreasureHold() {
    return _treasure_is_hold;
}

bool Player::isTreasureKeeper() {
    return _i_hold_treasure;
}

void Player::setTreasureHold(bool treasure_is_hold) {
    _treasure_is_hold = treasure_is_hold;
}

void Player::setTreasureKeeper(bool i_hold_treasure) {
    _i_hold_treasure = i_hold_treasure;
    if (_i_hold_treasure) {
        _treasure_is_hold = _i_hold_treasure;
    }
}