#ifndef TASK4_GAME_BOT_H
#define TASK4_GAME_BOT_H

#include <list>
#include <stack>
#include "Player.h"

class Bot : public Player {
private:
    std::stack<Direction> _path_to_undiscovered;

    std::map<Direction, std::pair<int, int>> getCandidates(std::pair<int, int> pos);
    bool containsUndiscovered(std::map<Direction, std::pair<int, int>>& candidates);
    std::stack<Direction> findPathToUndiscovered(std::pair<int, int> pos);

public:
    Bot(const std::pair<int, int> &start_pos, const std::list<std::string>& all_actions);

    std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out) override;
    bool isBot() override;
    bool getAnswer(std::istream& in, std::ostream& out, char cell_sym) override;
    void endTurn(std::istream& in, std::ostream& out) override;
};


#endif //TASK4_GAME_BOT_H
