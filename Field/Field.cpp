#include "Field.h"

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
