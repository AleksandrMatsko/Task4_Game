#ifndef TASK4_GAME_POSSIBLECELLS_H
#define TASK4_GAME_POSSIBLECELLS_H

#include "Cell.h"
#include "CellFactory.h"

class Wall : public Cell {
private:
    char _cell_sym;
    bool _passable;
    bool _interactive;
    bool _shoot_through;

public:
    Wall();

    char getCellSym() {
        return _cell_sym;
    }
    bool canStand() {
        return _passable;
    }
    bool canInteract() {
        return _interactive;
    }
    bool canShootThrough() {
        return _shoot_through;
    }
};

class Passage : public Cell {
private:
    char _cell_sym;
    bool _passable;
    bool _interactive;
    bool _shoot_through;

public:
    Passage();

    char getCellSym() {
        return _cell_sym;
    }
    bool canStand() {
        return _passable;
    }
    bool canInteract() {
        return _interactive;
    }
    bool canShootThrough() {
        return _shoot_through;
    }
};

class Exit : public Cell {
private:
    char _cell_sym;
    bool _passable;
    bool _interactive;
    bool _shoot_through;

public:
    Exit();

    char getCellSym() {
        return _cell_sym;
    }
    bool canStand() {
        return _passable;
    }
    bool canInteract() {
        return _interactive;
    }
    bool canShootThrough() {
        return _shoot_through;
    }
};

class Treasure : public Cell {
private:
    char _cell_sym;
    bool _passable;
    bool _interactive;
    bool _shoot_through;

public:
    Treasure();

    char getCellSym() {
        return _cell_sym;
    }
    bool canStand() {
        return _passable;
    }
    bool canInteract() {
        return _interactive;
    }
    bool canShootThrough() {
        return _shoot_through;
    }
};


#endif //TASK4_GAME_POSSIBLECELLS_H
