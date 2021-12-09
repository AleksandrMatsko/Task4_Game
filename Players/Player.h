#ifndef TASK4_GAME_PLAYER_H
#define TASK4_GAME_PLAYER_H

#include <vector>
#include <string>
#include <limits>
#include "../Field.h"

namespace StrModifier {
    void ToLower(std::string& str);
}

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

Direction operator!(Direction direction);
void printDirection(Direction direction, std::ostream& out);

class Player {
private:
    std::pair<int, int> _pos;
    std::shared_ptr<OpenField> _open_field;
    bool _skip_turn;
    std::map<std::string, bool> _possible_actions;
    bool _treasure_is_hold;
    bool _i_hold_treasure;

public:
    Player(const std::pair<int, int>& start_pos, int width, int height, const std::map<std::string, bool>& possible_actions);

    virtual std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out);
    virtual void setPosition(const std::pair<int, int>& new_pos);
    virtual std::pair<int, int> getPosition();
    virtual bool isSkip();
    virtual void setActionMode(const std::string& action, bool mode);
    virtual void setSkipMode(bool mode);
    virtual std::shared_ptr<OpenField> getOpenedField();
    virtual bool isAvailable(const std::string& action);
    virtual bool isBot();
    virtual bool isTreasureHold();
    virtual bool isTreasureKeeper();
    virtual void setTreasureHold(bool treasure_is_hold);
    virtual void setTreasureKeeper(bool i_hold_treasure);
};


#endif //TASK4_GAME_PLAYER_H