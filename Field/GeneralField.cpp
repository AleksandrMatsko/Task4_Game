#include "GeneralField.h"

GeneralField::GeneralField() : Field() {
    _field = {'*', '*', '*', '*', '*', '*', '*', '*', '*',
              '*', '0', '1', '0', '*', '0', '0', '0', '*',
              '*', '0', '*', '0', '0', '0', '*', 'T', '*',
              '*', '0', '0', '*', '*', '0', '3', '*', '*',
              '*', '0', '*', '*', '0', '0', '0', '*', '*',
              '*', '0', '4', '0', '0', '*', '0', '2', '*',
              '*', '0', '*', '0', '*', '0', '*', '0', '*',
              '*', '0', '0', '0', '*', '0', '0', '0', '*',
              '*', '*', 'E', '*', '*', '*', '*', '*', '*'};

    std::srand(std::time(nullptr));
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
    }
}

void GeneralField::printField(std::ostream& out) {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            out << _field[i * _width + j] << " ";
        }
        out << std::endl;
    }
}
