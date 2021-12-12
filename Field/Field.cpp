#include "Field.h"

Direction operator!(Direction direction) {
    if (direction == Direction::UP) {
        return Direction::DOWN;
    }
    else if (direction == Direction::DOWN) {
        return Direction::UP;
    }
    else if(direction == Direction::RIGHT) {
        return Direction::LEFT;
    }
    else if(direction == Direction::LEFT) {
        return Direction::RIGHT;
    }
    else {
        return Direction::NONE;
    }
}

Field::Field() {
    _width = 9;
    _height = 9;
}

std::vector<char>& Field::getField() {
    return _field;
}

char Field::viewCell(const std::pair<int, int> &pos) {
    return _field[pos.first * _width + pos.second];
}

void Field::changeCell(const std::pair<int, int>& pos, char new_cell_sym) {
    _field[pos.first * _width + pos.second] = new_cell_sym;
}

int Field::getHeight() {
    return _height;
}

int Field::getWidth() {
    return _width;
}
