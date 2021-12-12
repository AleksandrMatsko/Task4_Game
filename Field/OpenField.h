#ifndef TASK4_GAME_OPENFIELD_H
#define TASK4_GAME_OPENFIELD_H

#include "Field.h"

class OpenField : public Field {
public:
    OpenField();
    void printField(std::ostream& out) override;
};


#endif //TASK4_GAME_OPENFIELD_H
