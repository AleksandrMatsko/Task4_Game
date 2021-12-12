#ifndef TASK4_GAME_PLAYER_H
#define TASK4_GAME_PLAYER_H

#include <list>
#include <vector>
#include <string>
#include <limits>
#include "../Printer.h"
#include "../Field/OpenField.h"

namespace StrModifier {
    void ToLower(std::string& str);
}

class Player {
private:
    std::pair<int, int> _pos;
    OpenField _open_field;
    bool _skip_turn;
    std::map<std::string, bool> _possible_actions;
    bool _treasure_is_hold;
    bool _i_hold_treasure;

public:
    Player(const std::pair<int, int>& start_pos, const std::list<std::string>& all_actions);

    virtual std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out) = 0;
    virtual bool isBot() = 0;
    virtual bool getAnswer(std::istream& in, std::ostream& out, char cell_sym) = 0;
    virtual void endTurn(std::istream& in, std::ostream& out) = 0;

    void setPosition(const std::pair<int, int>& new_pos);
    void setActionMode(const std::string& action, bool mode);
    void setSkipMode(bool mode);
    void setTreasureHold(bool treasure_is_hold);
    void setTreasureKeeper(bool i_hold_treasure);

    std::pair<int, int> getPosition();
    bool isSkip();
    OpenField& getOpenedField();
    const std::map<std::string, bool>& getPossibleActions();
    bool isAvailable(const std::string& action);
    bool isTreasureHold();
    bool isTreasureKeeper();
};



#endif //TASK4_GAME_PLAYER_H
