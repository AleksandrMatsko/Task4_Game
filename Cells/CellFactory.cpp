#include <iostream>
#include "CellFactory.h"

CellFactory& CellFactory::Instance() {
    static CellFactory factory;
    return factory;
}

void CellFactory::Register(char cell_sym, std::shared_ptr<Cell> cell) {
    if (_cells.find(cell_sym) != _cells.end()) {
        throw InvalidCellRegistration(cell_sym);
    }
    _cells[cell_sym] = std::move(cell);
}

std::shared_ptr<Cell> CellFactory::getCell(char cell_sym) {
    if (_cells.find(cell_sym) == _cells.end()) {
        throw InvalidCellSymbol(cell_sym);
    }
    return _cells[cell_sym];
}

bool CellFactory::hasCell(char cell_sym) {
    return _cells.find(cell_sym) != _cells.end();
}