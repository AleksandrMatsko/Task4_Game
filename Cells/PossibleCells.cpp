#include "PossibleCells.h"

namespace {
    bool RegisterCells() {
        CellFactory::Instance().Register('*', makeCell<Wall>());
        CellFactory::Instance().Register('0', makeCell<Passage>());
        CellFactory::Instance().Register('E', makeCell<Exit>());
        CellFactory::Instance().Register('T', makeCell<Treasure>());
        return true;
    }

    static bool fake = RegisterCells();
}

Wall::Wall() {
    _cell_sym = '*';
    _passable = false;
    _interactive = false;
    _shoot_through = false;
}

Passage::Passage() {
    _cell_sym = '0';
    _passable = true;
    _interactive = false;
    _shoot_through = true;
}

Exit::Exit() {
    _cell_sym = 'E';
    _passable = true;
    _interactive = true;
    _shoot_through = false;
}

Treasure::Treasure() {
    _cell_sym = 'T';
    _passable = true;
    _interactive = true;
    _shoot_through = true;
}
