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
    std::shared_ptr<Field> getField();
};

const std::string rules = "Hello everyone!\n"
                          "Here are the rules of the game:\n"
                          "Max amount of players - 4, min - 0. Each player should have unique name.\n"
                          "Your purpose is to escape the maze with the treasure, which is located inside the labyrinth.\n\n"
                          "Some information about maze cells:\n"
                          "0 - means that cell is passable, so you can move on it\n"
                          "* - means wall, you can't step on it, you can't shoot through it\n"
                          "E - means exit\n"
                          "T - means treasure\n\n"
                          "Let's speak about actions:\n"
                          "You can do 2 actions (move, shoot) in 4 directions (up, down, left, right).\n"
                          "You can't shoot two turns in a row or if you hold a treasure.\n"
                          "If the player was shot, he (or she) would skip one turn.\n"
                          "Moreover if the player was holding the treasure it would be dropped on the cell player was standing.\n\n"
                          "Each turn you will be shown a part of maze you have already discovered.\n\n\n"
                          "Good luck!\n\n"
                          "Let's start:\n";

#endif //TASK4_GAME_GAMEMANAGER_H
