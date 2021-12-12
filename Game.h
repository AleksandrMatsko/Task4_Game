#ifndef TASK4_GAME_GAME_H
#define TASK4_GAME_GAME_H

#include "GameManager.h"

class Game {
private:
    std::list<std::string> _player_names;

public:
    Game(std::istream& in, std::ostream& out);
    void start(std::istream& in, std::ostream& out);
};


#endif //TASK4_GAME_GAME_H
