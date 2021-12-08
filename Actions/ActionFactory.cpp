#include "ActionFactory.h"

ActionFactory& ActionFactory::Instance() {
    static ActionFactory factory;
    return factory;
}

void ActionFactory::Register(const std::string &act_name, std::shared_ptr<Action> action) {
    if (hasAction(act_name)) {
        //exception
    }
    _actions[act_name] =  std::move(action);
    _reg_actions.emplace_back(act_name);
}

std::shared_ptr<Action> ActionFactory::getAction(const std::string& act_name) {
    if (!hasAction(act_name)) {
        //exception
    }
    return _actions[act_name];
}

const std::list<std::string>& ActionFactory::getAllActions() {
    return _reg_actions;
}

bool ActionFactory::hasAction(const std::string& act_name) {
    return _actions.find(act_name) != _actions.end();
}