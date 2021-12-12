#include "HumanPlayer.h"

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

HumanPlayer::HumanPlayer(const std::pair<int, int>& start_pos,
                         const std::list<std::string>& all_actions) : Player(start_pos, all_actions) {}

std::pair<std::string, Direction> HumanPlayer::chooseAction(std::istream& in, std::ostream& out) {
    out << "You can do these actions:" << std::endl;
    auto possible_actions = getPossibleActions();
    for (auto & it: possible_actions) {
        if (it.second) {
            out << "- " << it.first << std::endl;
        }
    }
    auto action_name = GetNameAction(in, out, possible_actions);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto direction = GetDirection(in, out);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_pair(action_name, direction);
}

bool HumanPlayer::isBot() {
    return false;
}