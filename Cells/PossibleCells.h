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
    const bool canStand() {
        return _passable;
    }
    const bool canInteract() {
        return _interactive;
    }
    const bool canShootThrough() {
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
    const bool canStand() {
        return _passable;
    }
    const bool canInteract() {
        return _interactive;
    }
    const bool canShootThrough() {
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
    const bool canStand() {
        return _passable;
    }
    const bool canInteract() {
        return _interactive;
    }
    const bool canShootThrough() {
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
    const bool canStand() {
        return _passable;
    }
    const bool canInteract() {
        return _interactive;
    }
    const bool canShootThrough() {
        return _shoot_through;
    }
};


#endif //TASK4_GAME_POSSIBLECELLS_H
