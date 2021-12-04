#ifndef TASK4_GAME_PLAYER_H
#define TASK4_GAME_PLAYER_H

#include <vector>
#include <string>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player {
private:
    std::pair<int, int> _pos;
    std::vector<char> _open_field;

protected:
    std::vector<char>& getOpenField();

public:
    bool makeTurn(const std::string& action, Direction direction);
    std::pair<int, int> getPosition();
    void setField(std::vector<char>& field);
};


#endif //TASK4_GAME_PLAYER_H
