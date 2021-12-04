#ifndef TASK4_GAME_CELL_H
#define TASK4_GAME_CELL_H

class Cell {
public:
    virtual const bool canStand() = 0;
    virtual const bool canInteract() = 0;
    virtual const bool canShootThrough() = 0;
    virtual ~Cell() {}
};


#endif //TASK4_GAME_CELL_H
