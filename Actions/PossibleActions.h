#ifndef TASK4_GAME_POSSIBLEACTIONS_H
#define TASK4_GAME_POSSIBLEACTIONS_H

#include "ActionFactory.h"

class Move : public Action {
public:
    bool doAction(const std::string& player_name,
                  std::map<std::string, std::shared_ptr<Player>>& players,
                  Field& field, Direction direction, std::istream& in,
                  std::ostream& out, std::string& hold_treasure, bool& end_game);
};

class Shoot : public Action {
public:
    bool doAction(const std::string& player_name,
                  std::map<std::string, std::shared_ptr<Player>>& players,
                  Field& field, Direction direction, std::istream& in,
                  std::ostream& out, std::string& hold_treasure, bool& end_game);
};

#endif //TASK4_GAME_POSSIBLEACTIONS_H
