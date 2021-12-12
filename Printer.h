#ifndef TASK4_GAME_PRINTER_H
#define TASK4_GAME_PRINTER_H

#include <istream>
#include "Field/Field.h"

class Printer {
public:
    void printRules(std::ostream& out);
    void printChoiceNumberPlayers(std::ostream& out);
    void printChoiceName(std::ostream& out, int number);
    void printNameOccupied(std::ostream& out);
    void printWhoseTurn(std::ostream& out, const std::string& name);
    void printTreasureInformation(std::ostream& out, bool is_treasure_keeper, bool is_treasure_hold);
    void printField(std::ostream& out, Field& field);
    void printExitFound(std::ostream& out);
    void printTreasureFound(std::ostream& out);
    void printWasShot(std::ostream& out);
    void printEndTurn(std::ostream& out);
    void printChoiceAnswer(std::ostream& out);
    void printChoiceDirection(std::ostream& out);
    void printDirection(std::ostream& out, Direction direction);
    void printChoiceAction(std::ostream& out);
    void printPossibleActions(std::ostream& out, const std::map<std::string, bool>& possible_actions);
    void printAction(std::ostream& out, const std::string& act_name, Direction direction);
    void printIsActionSuccess(std::ostream& out, const std::string& act_name, bool is_success);
    void printWinner(std::ostream& out, const std::string& winner);
};


#endif //TASK4_GAME_PRINTER_H
