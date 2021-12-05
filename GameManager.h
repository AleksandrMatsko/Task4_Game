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
    std::shared_ptr<Field> _field;
    std::string _hold_treasure;
    bool _end_game;

    GameManager(const std::list<std::string>& player_names);
    void makeTurn(const std::string& player_name, const std::pair<std::string, Direction>& action,
                  std::istream& in, std::ostream& out);
    std::pair<int, int> movePos(const std::pair<int, int>& pos, Direction direction);

public:
    GameManager(GameManager& gm) = delete;
    GameManager& operator=(GameManager& gm) = delete;

    static GameManager& Instance(const std::list<std::string>& player_names);
    bool makeRound(std::istream& in, std::ostream& out);
};


#endif //TASK4_GAME_GAMEMANAGER_H
