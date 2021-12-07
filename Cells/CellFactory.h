#ifndef TASK4_GAME_CELLFACTORY_H
#define TASK4_GAME_CELLFACTORY_H

#include <map>
#include <memory>
#include "Cell.h"

template <typename T>
std::shared_ptr<Cell> makeCell() {
    std::shared_ptr<T> cell = std::make_shared<T>();
    return cell;
}

class CellFactory {
private:
    std::map<char, std::shared_ptr<Cell>> _cells;
    CellFactory() = default;
public:
    CellFactory(CellFactory& b) = delete;
    CellFactory& operator=(CellFactory& b) = delete;

    static CellFactory& Instance();
    void Register(const char cell_sym, std::shared_ptr<Cell> cell);
    std::shared_ptr<Cell> getCell(const char cell_sym);
    bool hasCell(const char cell_sym);
};


#endif //TASK4_GAME_CELLFACTORY_H
