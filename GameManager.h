#ifndef TASK4_GAME_GAMEMANAGER_H
#define TASK4_GAME_GAMEMANAGER_H

#include <map>
#include "Actions/ActionFactory.h"
#include "Cells/CellFactory.h"

class GameManager {
private:
    std::list<std::string> _names;
    std::map<std::string, std::shared_ptr<Player>> _players;
    std::shared_ptr<Field> _field;
    std::string _hold_treasure;
    bool _end_game;

    GameManager(const std::list<std::string>& player_names);

public:
    GameManager(GameManager& gm) = delete;
    GameManager& operator=(GameManager& gm) = delete;

    static GameManager& Instance(const std::list<std::string>& player_names);
    bool makeRound(std::istream& in, std::ostream& out);
    const std::string& getHoldTreasure();
};


#endif //TASK4_GAME_GAMEMANAGER_H
