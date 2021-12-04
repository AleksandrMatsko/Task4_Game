#ifndef TASK4_GAME_GAMEMANAGER_H
#define TASK4_GAME_GAMEMANAGER_H

#include <memory>
#include <map>
#include <list>
#include "Player.h"
#include "Cells/CellFactory.h"

class GameManager {
private:
    std::map<std::string, std::shared_ptr<Player>> _players;
    std::map<std::string, bool> _skip_turn;
    std::map<std::string, bool> _can_shoot;
    std::vector<char> _field;
    std::string _hold_treasure;

public:
    GameManager(const std::list<std::string>& player_names);
    void makeRound();
};


#endif //TASK4_GAME_GAMEMANAGER_H
