#include "Exception.h"

InvalidCellRegistration::InvalidCellRegistration(char cell_sym) {
    _message = "Error: cell with symbol - " + std::string(1, cell_sym) + " already exists.";
    _cell_sym = cell_sym;
}

char InvalidCellRegistration::getCellSym() {
    return _cell_sym;
}

const char *InvalidCellRegistration::what() {
    return _message.c_str();
}

InvalidCellSymbol::InvalidCellSymbol(char cell_sym) {
    _message = "Error: invalid cell symbol - " + std::string(1, cell_sym) + ".";
    _cell_sym = cell_sym;
}

char InvalidCellSymbol::getCellSym() {
    return _cell_sym;
}

const char *InvalidCellSymbol::what() {
    return _message.c_str();
}

InvalidActionRegistration::InvalidActionRegistration(const std::string &act_name) {
    _message = "Error: action with name - " + act_name + " already exists.";
    _act_name = act_name;
}

const std::string &InvalidActionRegistration::getActionName() {
    return _act_name;
}

const char *InvalidActionRegistration::what() {
    return _message.c_str();
}

InvalidActionName::InvalidActionName(const std::string &act_name) {
    _message = "Error: invalid action name - " + act_name + ".";
    _act_name = act_name;
}

const std::string &InvalidActionName::getActionName() {
    return _act_name;
}

const char *InvalidActionName::what() {
    return _message.c_str();
}
