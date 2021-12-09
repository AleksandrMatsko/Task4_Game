#ifndef TASK4_GAME_BOT_H
#define TASK4_GAME_BOT_H

#include <list>
#include <stack>
#include "Player.h"

class Bot : public Player {
private:
    std::pair<int, int> _pos;
    std::shared_ptr<OpenField> _open_field;
    bool _skip_turn;
    std::map<std::string, bool> _possible_actions;
    bool _exit_found;
    std::stack<Direction> _path_exit;
    bool _treasure_is_hold;
    bool _i_hold_treasure;
    std::stack<Direction> _path_to_undiscovered;

    std::map<Direction, std::pair<int, int>> getCandidates(std::pair<int, int> pos);
    bool containsUndiscovered(std::map<Direction, std::pair<int, int>>& candidates);
    std::stack<Direction> findPathToUndiscovered(std::pair<int, int> pos);

public:
    Bot(const std::pair<int, int> &start_pos, int width,
        int height, const std::map<std::string, bool> &possible_actions);

    std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out);
    void setPosition(const std::pair<int, int>& new_pos);
    std::pair<int, int> getPosition();
    bool isSkip();
    void setActionMode(const std::string& action, bool mode);
    void setSkipMode(bool mode);
    std::shared_ptr<OpenField> getOpenedField();
    bool isAvailable(const std::string& action);
    bool isBot();
    bool isTreasureHold();
    bool isTreasureKeeper();
    void setTreasureHold(bool treasure_is_hold);
    void setTreasureKeeper(bool i_hold_treasure);
    void setExitFound(bool exit_found);
};


#endif //TASK4_GAME_BOT_H
