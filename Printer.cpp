#include "Printer.h"

void Printer::printRules(std::ostream& out) {
    out << "Hello everyone!" << std::endl <<
        "Here are the rules of the game:" << std::endl <<
        "Max amount of players - 4, min - 0. Each player should have unique name." << std::endl << std::endl <<
        "Your purpose is to escape the maze with the treasure, which is located inside the labyrinth." << std::endl << std::endl <<
        "Some information about maze cells:" << std::endl <<
        "0 - means that cell is passable, so you can move on it" << std::endl <<
        "* - means wall, you can't step on it, you can't shoot through it" << std::endl <<
        "E - means exit" << std::endl <<
        "T - means treasure" << std::endl << std::endl <<
        "Let's speak about actions:" << std::endl <<
        "You can do 2 actions (move, shoot) in 4 directions (up, down, left, right)." << std::endl <<
        "You can't shoot two turns in a row or if you hold a treasure." << std::endl <<
        "If the player was shot, he (or she) would skip one turn." << std::endl <<
        "Moreover if the player was holding the treasure it would be dropped on the cell player was standing." << std::endl << std::endl <<
        "Each turn you will be shown a part of maze you have already discovered." << std::endl << std::endl << std::endl <<
        "Good luck!" << std::endl << std::endl <<
        "Let's start:" << std::endl;
}

void Printer::printChoiceNumberPlayers(std::ostream &out) {
    std::cout << "Please enter number of players (from 1 to 4):" << std::endl;
}

void Printer::printChoiceName(std::ostream &out, int number) {
    std::cout << "Please enter the name of " << number << " player" << std::endl;
}

void Printer::printNameOccupied(std::ostream &out) {
    std::cout << "Name already entered" << std::endl;
}

void Printer::printWhoseTurn(std::ostream &out, const std::string &name) {
    out << "Turn: " << name << std::endl;
}

void Printer::printTreasureInformation(std::ostream& out, bool is_treasure_keeper, bool is_treasure_hold) {
    if (is_treasure_keeper) {
        out << std::endl;
        out << "You hold treasure" << std::endl;
        out << std::endl;
    }
    if (!is_treasure_keeper && is_treasure_hold) {
        out << std::endl;
        out << "!!!!!!!!!!!!ATTENTION!!!!!!!!!!!!" << std::endl;
        out << std::endl;
        out << "Someone hold treasure" << std::endl;
        out << std::endl;
        out << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        out << std::endl;
    }
}

void Printer::printField(std::ostream &out, Field &field) {
    field.printField(out);
}

void Printer::printExitFound(std::ostream &out) {
    out << "You found an exit. Do you want to leave maze?" << std::endl;
    out << "If you don't hold a treasure you will leave the game. What's your answer?" << std::endl;
}

void Printer::printTreasureFound(std::ostream &out) {
    out << "You found a treasure. Do you want to pick it up?" << std::endl;
    out << "After picking up a treasure you can't shoot. What's your answer?" << std::endl;
}

void Printer::printWasShot(std::ostream &out) {
    out << "You've been shot, so you need one turn to heal" << std::endl;
}

void Printer::printEndTurn(std::ostream &out) {
    out << "Enter anything to end turn" << std::endl;
}

void Printer::printChoiceAnswer(std::ostream &out) {
    out << std::endl;
    out << "Please enter [yes] or [no] (without [])" << std::endl;
}

void Printer::printChoiceDirection(std::ostream &out) {
    out << "Please choose 1 of 4 directions (up, down, left, right):" << std::endl;
}

void Printer::printDirection(std::ostream& out, Direction direction) {
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

void Printer::printChoiceAction(std::ostream &out) {
    out << "Please choose one action (after choosing the action you will be asked about direction):" << std::endl;
}

void Printer::printPossibleActions(std::ostream &out, const std::map<std::string, bool> &possible_actions) {
    out << "You can do these actions:" << std::endl;
    for (auto & it: possible_actions) {
        if (it.second) {
            out << "- " << it.first << std::endl;
        }
    }
}

void Printer::printAction(std::ostream &out, const std::string &act_name, Direction direction) {
    out << act_name << " ";
    printDirection(out, direction);
    out << std::endl;
}

void Printer::printIsActionSuccess(std::ostream &out, const std::string &act_name, bool is_success) {
    if (act_name == "move") {
        if (is_success) {
            out << "Success" << std::endl;
        }
        else {
            out << "Failure. You've found unpassable cell" << std::endl;
        }
    }
    if (act_name == "shoot") {
        if (is_success) {
            out << std::endl;
            out << "=================================" << std::endl;
            out << std::endl;
            out << "You've shot somebody" << std::endl;
            out << std::endl;
            out << "=================================" << std::endl;
            out << std::endl;
        }
        else {
            out << std::endl;
            out << "=================================" << std::endl;
            out << std::endl;
            out << "You haven't shot anybody" << std::endl;
            out << std::endl;
            out << "=================================" << std::endl;
            out << std::endl;
        }
    }
}

void Printer::printWinner(std::ostream &out, const std::string &winner) {
    out << std::endl;
    if (winner.empty()) {
        out << "Nobody win" << std::endl;
    }
    else {
        out << "!!!  Winner: " << winner << "  !!!" << std::endl;
    }
    out << std::endl;
}
