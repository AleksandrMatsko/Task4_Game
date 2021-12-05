#ifndef TASK4_GAME_PLAYER_H
#define TASK4_GAME_PLAYER_H

#include <vector>
#include <string>
#include "Field.h"

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Player {
private:
    std::pair<int, int> _pos;
    std::shared_ptr<OpenField> _open_field;
    bool _skip_turn;
    bool _can_shoot;

public:
    Player(const std::pair<int, int>& start_pos, int width, int height);

    std::pair<std::string, Direction> chooseAction(std::istream& in, std::ostream& out);
    void setPosition(const std::pair<int, int>& new_pos);
    std::pair<int, int> getPosition();
    bool isSkip();
    bool canShoot();
    void setShootMode(bool mode);
    void setSkipMode(bool mode);
    std::shared_ptr<OpenField> getOpenedField();
};


#endif //TASK4_GAME_PLAYER_H
