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
        auto open_field = this->getOpenedField();
        auto cell_sym = open_field.viewCell(new_pos);
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
    auto open_field = this->getOpenedField();
    for (auto & candidate : candidates) {
        if (open_field.viewCell(candidate.second) == '?') {
            return true;
        }
    }
    return false;
}

std::stack<Direction> Bot::findPathToUndiscovered(std::pair<int, int> pos) {
    std::list<std::pair<int, int>> queue;
    std::map<std::pair<int, int>, Direction> all_steps;
    auto open_field = this->getOpenedField();
    int width = open_field.getWidth();
    int height = open_field.getHeight();
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
        if (open_field.viewCell(curr_pos) == '?') {
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

Bot::Bot(const std::pair<int, int> &start_pos, const std::list<std::string>& all_actions) : Player(start_pos, all_actions) {}

std::pair<std::string, Direction> Bot::chooseAction(std::istream &in, std::ostream &out) {
    std::srand(std::time(nullptr));
    Direction direction = Direction::NONE;
    std::pair<std::string, Direction> ret;
    if (!isTreasureHold() || !isAvailable("shoot")) {
        if (!_path_to_undiscovered.empty()) {
            direction = _path_to_undiscovered.top();
            ret = std::make_pair("move", direction);
            _path_to_undiscovered.pop();
            return ret;
        }
        auto candidates = getCandidates(this->getPosition());
        bool contains_undiscovered = containsUndiscovered(candidates);
        if (contains_undiscovered) {
            std::list<Direction> to_del;
            for (auto & candidate : candidates) {
                auto cell_sym = this->getOpenedField().viewCell(candidate.second);
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
            _path_to_undiscovered = findPathToUndiscovered(this->getPosition());
            direction = _path_to_undiscovered.top();
            ret = std::make_pair("move", direction);
            _path_to_undiscovered.pop();
            return ret;
        }
    }
    if (isTreasureHold() && isAvailable("shoot")) {
        auto candidates = getCandidates(this->getPosition());
        auto rand_index = rand() % all_directions.size();
        while (candidates.find(all_directions[rand_index]) == candidates.end()) {
            rand_index = rand() % all_directions.size();
        }
        direction = all_directions[rand_index];
        ret = std::make_pair("shoot", direction);
        return ret;
    }
    if (ret.first.empty()) {
        ret.first = "move";
    }
    return ret;
}

bool Bot::isBot() {
    return true;
}

