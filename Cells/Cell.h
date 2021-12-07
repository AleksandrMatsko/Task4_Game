#ifndef TASK4_GAME_CELL_H
#define TASK4_GAME_CELL_H

class Cell {
public:
    virtual char getCellSym() = 0;
    virtual bool canStand() = 0;
    virtual bool canInteract() = 0;
    virtual bool canShootThrough() = 0;
    virtual ~Cell() {}
};


#endif //TASK4_GAME_CELL_H
