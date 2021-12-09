#ifndef TASK4_GAME_EXCEPTION_H
#define TASK4_GAME_EXCEPTION_H

#include <exception>
#include <string>

class InvalidCellRegistration : public std::exception {
private:
    std::string _message;
    char _cell_sym;

public:
    InvalidCellRegistration(char cell_sym);
    const char* what();
    char getCellSym();
};

class InvalidCellSymbol : public std::exception {
private:
    std::string _message;
    char _cell_sym;

public:
    InvalidCellSymbol(char cell_sym);
    const char* what();
    char getCellSym();
};

class InvalidActionRegistration : public std::exception {
private:
    std::string _message;
    std::string _act_name;

public:
    InvalidActionRegistration(const std::string& act_name);
    const char* what();
    const std::string& getActionName();
};

class InvalidActionName : public std::exception {
private:
    std::string _message;
    std::string _act_name;

public:
    InvalidActionName(const std::string& act_name);
    const char* what();
    const std::string& getActionName();
};



#endif //TASK4_GAME_EXCEPTION_H
