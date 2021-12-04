#ifndef TASK4_GAME_FIELD_H
#define TASK4_GAME_FIELD_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include "Cells/CellFactory.h"

class Field {
private:
    std::vector<char> _field;
    int _height;
    int _width;

public:
    Field();
    char viewCell(const std::pair<int, int>& pos);
    void changeCell(const std::pair<int, int>& pos, const char new_cell_sym);
    const std::vector<char>& getField();
    int getHeight();
    int getWidth();
};

class OpenField : public Field {
private:
    std::vector<char> _field;
    int _height;
    int _width;

public:
    OpenField(const std::pair<int, int>& pos, const int width, const int height);
};


#endif //TASK4_GAME_FIELD_H
