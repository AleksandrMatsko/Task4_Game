#include "CellFactory.h"

CellFactory& CellFactory::Instance() {
    static CellFactory factory;
    return factory;
}

void CellFactory::Register(const char cell_sym, std::shared_ptr<Cell> cell) {
    if (_cells.find(cell_sym) != _cells.end()) {
        //exception
    }
    _cells[cell_sym] = std::move(cell);
}

std::shared_ptr<Cell> CellFactory::getCell(const char cell_sym) {
    return _cells[cell_sym];
}

bool CellFactory::hasCell(const char cell_sym) {
    return _cells.find(cell_sym) != _cells.end();
}