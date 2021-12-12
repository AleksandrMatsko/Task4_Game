#ifndef TASK4_GAME_ACTIONFACTORY_H
#define TASK4_GAME_ACTIONFACTORY_H

#include "Action.h"
#include "../Exceptions/Exception.h"

template <typename T>
std::shared_ptr<Action> actionMaker() {
    std::shared_ptr<T> act = std::make_shared<T>();
    return act;
}

class ActionFactory {
private:
    std::map<std::string, std::shared_ptr<Action>> _actions;
    std::list<std::string> _reg_actions;
    ActionFactory() = default;

public:
    ActionFactory(ActionFactory &a) = delete;
    ActionFactory& operator=(ActionFactory &a) = delete;

    static ActionFactory& Instance();
    void Register(const std::string &act_name, std::shared_ptr<Action> action);
    std::shared_ptr<Action> getAction(const std::string &act_name);
    const std::list<std::string>& getAllActions();
    bool hasAction(const std::string& act_name);
};


#endif //TASK4_GAME_ACTIONFACTORY_H
