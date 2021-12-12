#include "Player.h"

namespace StrModifier {
    void ToLower(std::string &str) {
        for (int i = 0; i < str.size(); i++) {
            str[i] = char(std::tolower(str[i]));
        }
    }
}

Player::Player(const std::pair<int, int>& start_pos, const std::list<std::string>& all_actions) {
    _pos = start_pos;
    _open_field = OpenField();
    _skip_turn = false;
    for (auto & it: all_actions) {
        _possible_actions[it] = true;
    }
    _open_field.changeCell(start_pos, 'P');
    _treasure_is_hold = false;
    _i_hold_treasure = false;
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

OpenField& Player::getOpenedField() {
    return _open_field;
}

const std::map<std::string, bool> &Player::getPossibleActions() {
    return _possible_actions;
}

bool Player::isAvailable(const std::string& action) {
    return _possible_actions[action];
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
}
