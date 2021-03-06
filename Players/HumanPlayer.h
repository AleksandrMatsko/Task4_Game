#ifndef TASK4_GAME_HUMANPLAYER_H
#define TASK4_GAME_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::pair<int, int>& start_pos, const std::list<std::string>& all_actions);

    std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out) override;
    bool isBot() override;
    bool getAnswer(std::istream& in, std::ostream& out, char cell_sym) override;
    void endTurn(std::istream& in, std::ostream& out) override;
};


#endif //TASK4_GAME_HUMANPLAYER_H
