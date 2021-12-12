#ifndef TASK4_GAME_FIELD_H
#define TASK4_GAME_FIELD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../Cells/CellFactory.h"

class Field {
protected:
    std::vector<char> _field;
    int _height;
    int _width;

public:
    Field();

    virtual void printField(std::ostream& out) = 0;

    void changeCell(const std::pair<int, int>& pos, char new_cell_sym);

    char viewCell(const std::pair<int, int>& pos);
    std::vector<char>& getField();
    int getHeight();
    int getWidth();
};


#endif //TASK4_GAME_FIELD_H
