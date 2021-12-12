#ifndef TASK4_GAME_ACTION_H
#define TASK4_GAME_ACTION_H

#include <memory>
#include "../Players/HumanPlayer.h"
#include "../Players/Bot.h"

namespace Additional {
    bool GetAnswer(std::istream& in, std::ostream& out);
    void operateTreasure(std::pair<int, int> pos, const std::string& player_name,
                         std::map<std::string, std::shared_ptr<Player>>& players,
                         Field& field, std::istream& in, std::ostream& out,
                         std::string& hold_treasure);
}

class Action {
public:
    virtual bool doAction(const std::string& player_name,
                          std::map<std::string, std::shared_ptr<Player>>& players,
                          Field& field, Direction direction, std::istream& in,
                          std::ostream& out, std::string& hold_treasure, bool& end_game) = 0;
    virtual ~Action() {}
};

#endif //TASK4_GAME_ACTION_H
