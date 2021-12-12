#ifndef TASK4_GAME_GENERALFIELD_H
#define TASK4_GAME_GENERALFIELD_H

#include "Field.h"

class GeneralField : public Field {
public:
    GeneralField();
    void printField(std::ostream& out) override;
};


#endif //TASK4_GAME_GENERALFIELD_H
