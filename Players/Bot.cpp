#include "Bot.h"

namespace {
    std::pair<int, int> movePos(const std::pair<int, int> &pos, Direction direction) {
        auto new_pos = pos;
        if (direction == Direction::UP) {
            new_pos.first -= 1;
        } else if (direction == Direction::DOWN) {
            new_pos.first += 1;
        } else if (direction == Direction::LEFT) {
            new_pos.second -= 1;
        } else if (direction == Direction::RIGHT) {
            new_pos.second += 1;
        }
        return new_pos;
    }

    const std::vector<Direction> all_directions = {Direction::DOWN, Direction::UP, Direction::LEFT, Direction::RIGHT};
}

std::map<Direction, std::pair<int, int>> Bot::getCandidates(std::pair<int, int> pos) {
    std::map<Direction, std::pair<int, int>> candidates;
    for (auto & direction : all_directions) {
        auto new_pos = movePos(pos, direction);
        auto cell_sym = _open_field->viewCell(new_pos);
        if (cell_sym == 'P') {
            continue;
        }
        if (cell_sym != '?' && cell_sym != 'E') {
            auto cell = CellFactory::Instance().getCell(cell_sym);
            if (!cell->canStand()) {
                continue;
            }
        }
        candidates[direction] = new_pos;

    }
    return candidates;
}

bool Bot::containsUndiscovered(std::map<Direction, std::pair<int, int>> &candidates) {
    for (auto & candidate : candidates) {
        if (_open_field->viewCell(candidate.second) == '?') {
            return true;
        }
    }
    return false;
}

std::stack<Direction> Bot::findPathToUndiscovered(std::pair<int, int> pos) {
    std::list<std::pair<int, int>> queue;
    std::map<std::pair<int, int>, Direction> all_steps;
    int width = _open_field->getWidth();
    int height = _open_field->getHeight();
    int size = width * height;
    std::vector<bool> is_used(size);
    for (int i = 0; i < size; i ++) {
        is_used[i] = false;
    }
    is_used[pos.first * width + pos.second] = true;
    for (auto & it : all_steps) {
        it.second = Direction::NONE;
    }
    std::pair<int, int> final_pos;
    queue.emplace_back(pos);
    while (!queue.empty()) {
        auto curr_pos = queue.front();
        if (_open_field->viewCell(curr_pos) == '?') {
            final_pos = curr_pos;
            break;
        }
        auto candidates = getCandidates(curr_pos);
        for (auto & candidate : candidates) {
            if (is_used[candidate.second.first * width + candidate.second.second]) {
                continue;
            }
            is_used[candidate.second.first * width + candidate.second.second] = true;
            queue.emplace_back(candidate.second);
            all_steps[candidate.second] = candidate.first;
        }
        queue.erase(queue.begin());
    }
    std::list<Direction> revert_path;
    while (final_pos != pos) {
        revert_path.emplace_back(all_steps[final_pos]);
        final_pos = movePos(final_pos, !all_steps[final_pos]);
    }
    std::stack<Direction> ret;
    for (auto & it : revert_path) {
        ret.push(it);
    }
    return ret;
}

Bot::Bot(const std::pair<int, int> &start_pos, int width,
         int height, const std::map<std::string, bool> &possible_actions) : Player(start_pos, width, height, possible_actions) {
    _pos = start_pos;
    _open_field = std::make_shared<OpenField>(start_pos, width, height);
    _skip_turn = false;
    _exit_found = false;
    _treasure_is_hold = false;
    _i_hold_treasure = false;
}

std::pair<std::string, Direction> Bot::chooseAction(std::istream &in, std::ostream &out) {
    std::srand(std::time(nullptr));
    Direction direction = Direction::NONE;
    std::pair<std::string, Direction> ret;
    if (!_treasure_is_hold || (_i_hold_treasure && !_exit_found) || (!isAvailable("shoot") && !_exit_found)) {
        if (!_path_to_undiscovered.empty()) {
            direction = _path_to_undiscovered.top();
            ret = std::make_pair("move", direction);
            _path_to_undiscovered.pop();
            if (_exit_found && !_i_hold_treasure && direction != Direction::NONE) {
                _path_exit.push(!direction);
            }
            return ret;
        }
        auto candidates = getCandidates(_pos);
        bool contains_undiscovered = containsUndiscovered(candidates);
        if (contains_undiscovered) {
            std::list<Direction> to_del;
            for (auto & candidate : candidates) {
                auto cell_sym = _open_field->viewCell(candidate.second);
                if (cell_sym != '?') {
                    to_del.emplace_back(candidate.first);
                }
            }
            for (auto & rm : to_del) {
                candidates.erase(rm);
            }
            auto rand_index = rand() % all_directions.size();
            while (candidates.find(all_directions[rand_index]) == candidates.end()) {
                rand_index = rand() % all_directions.size();
            }
            direction = all_directions[rand_index];
            ret = std::make_pair("move", direction);
        }
        else {
            while (!_path_to_undiscovered.empty()) {
                _path_to_undiscovered.pop();
            }
            _path_to_undiscovered = findPathToUndiscovered(_pos);
            direction = _path_to_undiscovered.top();
            ret = std::make_pair("move", direction);
            _path_to_undiscovered.pop();
        }
    }
    if (_exit_found && _i_hold_treasure) {
        direction = _path_exit.top();
        ret = std::make_pair("move", direction);
        _path_exit.pop();
        return ret;
    }
    if (_treasure_is_hold && isAvailable("shoot")) {
        auto candidates = getCandidates(_pos);
        auto rand_index = rand() % all_directions.size();
        while (candidates.find(all_directions[rand_index]) == candidates.end()) {
            rand_index = rand() % all_directions.size();
        }
        direction = all_directions[rand_index];
        ret = std::make_pair("shoot", direction);
    }
    if (ret.first.empty()) {
        ret.first = "move";
    }
    if (_exit_found && !_i_hold_treasure && direction != Direction::NONE) {
        _path_exit.push(!direction);
    }
    return ret;
}

void Bot::setPosition(const std::pair<int, int>& new_pos) {
    _pos = new_pos;
}

std::pair<int, int> Bot::getPosition() {
    return _pos;
}

bool Bot::isSkip() {
    return _skip_turn;
}

void Bot::setActionMode(const std::string &action, bool mode) {
    _possible_actions[action] = mode;
}

void Bot::setSkipMode(bool mode) {
    _skip_turn = mode;
}

std::shared_ptr<OpenField> Bot::getOpenedField() {
    return _open_field;
}

bool Bot::isAvailable(const std::string& action) {
    return _possible_actions[action];
}

bool Bot::isBot() {
    return true;
}

bool Bot::isTreasureHold() {
    return _treasure_is_hold;
}

bool Bot::isTreasureKeeper() {
    return _i_hold_treasure;
}

void Bot::setTreasureHold(bool treasure_is_hold) {
    _treasure_is_hold = treasure_is_hold;
}

void Bot::setTreasureKeeper(bool i_hold_treasure) {
    _i_hold_treasure = i_hold_treasure;
}

void Bot::setExitFound(bool exit_found) {
    _exit_found = exit_found;
}
