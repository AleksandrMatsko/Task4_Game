#include "Field.h"

Field::Field() {
    _field = {'*', '*', '*', '*', '*', '*', '*', '*', '*',
              '*', '0', '0', '0', '3', '0', '0', '0', '*',
              '*', '1', '*', '*', '*', '0', '*', 'T', '*',
              '*', '0', '0', '*', '0', '0', '0', '*', '*',
              '*', '0', '*', '*', '*', '0', '*', '*', '*',
              '*', '0', '4', '0', '0', '0', '0', '0', '*',
              '*', '0', '*', '0', '*', '*', '0', '2', '*',
              '*', '0', '0', '0', '*', '0', '0', '*', '*',
              '*', '*', '*', 'E', '*', '*', '*', '*', '*'};
    _width = 9;
    _height = _field.size() / _width;
    if (_field.size() != _width * _height) {
        //exception
    }
    for (auto & i : _field) {
        if (('0' > i || i > '9') && !CellFactory::Instance().hasCell(i)) {
            //exception
        }
    }
    /*std::srand(time(NULL));
    int flip_x = std::rand() % 2;
    int flip_y = std::rand() % 2;
    if (flip_x) {
        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width / 2 ; j++) {
                std::swap(_field[i * _width + j], _field[i * _width + _width - 1 - j]);
            }
        }
    }
    if (flip_y) {
        for (int i = 0; i < _height / 2; i++) {
            for (int j = 0; j < _width; j++) {
                std::swap(_field[i * _width + j], _field[(_height - 1 - i) * _width + j]);
            }
        }
    }*/
}

const std::vector<char>& Field::getField() {
    return _field;
}

char Field::viewCell(const std::pair<int, int> &pos) {
    return _field[pos.first * _width + pos.second];
}

void Field::changeCell(const std::pair<int, int>& pos, const char new_cell_sym) {
    _field[pos.first * _width + pos.second] = new_cell_sym;
}

int Field::getHeight() {
    return _height;
}

int Field::getWidth() {
    return _width;
}

OpenField::OpenField(const std::pair<int, int> &pos, const int width, const int height) {
    int size = width * height;
    _field = std::vector<char>(size);
    for (int i = 0; i < size; i++) {
        _field[i] = '?';
    }
    _field[pos.first * width + pos.second] = 'P';
}