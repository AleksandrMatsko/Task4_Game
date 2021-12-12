#include "HumanPlayer.h"

namespace {
    std::string GetNameAction(std::istream& in, std::ostream& out, std::map<std::string, bool> possible_actions) {
        Printer printer;
        std::string action;
        while (true) {
            printer.printChoiceAction(out);
            in >> action;
            StrModifier::ToLower(action);
            if (possible_actions.find(action) != possible_actions.end()) {
                bool available = possible_actions[action];
                if (available) {
                    return action;
                }
            }
        }
    }

    Direction GetDirection(std::istream& in, std::ostream& out) {
        Printer printer;
        std::string direction;
        while (true) {
            printer.printChoiceDirection(out);
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
        }
    }
}

HumanPlayer::HumanPlayer(const std::pair<int, int>& start_pos,
                         const std::list<std::string>& all_actions) : Player(start_pos, all_actions) {}

std::pair<std::string, Direction> HumanPlayer::chooseAction(std::istream& in, std::ostream& out) {
    auto possible_actions = this->getPossibleActions();
    Printer printer;
    printer.printPossibleActions(out, possible_actions);
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

bool HumanPlayer::getAnswer(std::istream &in, std::ostream &out, char cell_sym) {
    Printer printer;
    std::string answer;
    while (true) {
        printer.printChoiceAnswer(out);
        in >> answer;
        StrModifier::ToLower(answer);
        if (answer == "yes") {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if (answer == "no") {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
    }
}

void HumanPlayer::endTurn(std::istream &in, std::ostream &out) {
    std::string end_turn;
    in >> end_turn;
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < 25; i++) {
        out << std::endl;
    }
}