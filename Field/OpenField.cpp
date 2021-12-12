#include "OpenField.h"

OpenField::OpenField() : Field() {
    int size = _width * _height;
    _field = std::vector<char>(size);
    for (int i = 0; i < size; i++) {
        _field[i] = '?';
    }
}

void OpenField::printField(std::ostream &out) {
    out << "--------------------------" << std::endl;
    int num_fake_lines = 1;
    for (int i = 0; i < _width + 4; i++) {
        out << "? ";
        if (i == _width + 3 && num_fake_lines < 2) {
            i = -1;
            num_fake_lines += 1;
            out << std::endl;
        }
    }
    out << std::endl;
    for (int i = 0; i < _height; i++) {
        out << "? ? ";
        for (int j = 0; j < _width; j++) {
            out << _field[i * _width + j] << " ";
        }
        out << "? ?" << std::endl;
    }
    num_fake_lines = 1;
    for (int i = 0; i < _width + 4; i++) {
        out << "? ";
        if (i == _width + 3 && num_fake_lines < 2) {
            i = -1;
            num_fake_lines += 1;
            out << std::endl;
        }
    }
    out << std::endl;
    out << "--------------------------" << std::endl;
}
