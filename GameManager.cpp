#include "GameManager.h"

namespace {
    std::pair<int, int> GetStartPosition(const char num_player, std::shared_ptr<Field> f) {
        auto field = f->getField();
        auto height = f->getHeight();
        auto width = f->getWidth();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (field[i * width + j] == num_player) {
                    auto pos = std::make_pair(i, j);
                    f->changeCell(pos, '0');
                    return pos;
                }
            }
        }
        return std::make_pair(INT_MAX, INT_MAX);
    }
}

GameManager::GameManager(const std::list<std::string>& player_names) {
    std::srand(std::time(nullptr));
    _names = player_names;
    _end_game = false;
    _field = std::make_shared<Field>();
    auto all_actions = ActionFactory::Instance().getAllActions();
    std::map<std::string, bool> possible_actions;
    for (auto & it: all_actions) {
        possible_actions[it] = true;
    }
    char max_num_players = 4;
    std::vector<char> numbers = {'1', '2', '3', '4'};
    for (auto & player: _names) {
        char index = rand() % max_num_players;
        auto pos = GetStartPosition(numbers[index], _field);
        _players[player] = std::make_shared<Player>(pos, _field->getWidth(),
                                                    _field->getHeight(), possible_actions);
        _hold_treasure = "";
        numbers.erase(numbers.begin() + index);
        max_num_players -= 1;
    }
    for (auto number : numbers) {
        auto pos = GetStartPosition(number, _field);
        std::string bot_name = "Bot_" + std::to_string(number);
        while (_players.find(bot_name) != _players.end()) {
            bot_name += std::to_string(char(rand() % 64));
        }
        _names.emplace_back(bot_name);
        _players[bot_name] = std::make_shared<Bot>(pos, _field->getWidth(),
                                                   _field->getHeight(), possible_actions);
    }
}

GameManager& GameManager::Instance(const std::list<std::string>& player_names) {
    static GameManager manager(player_names);
    return manager;
}

bool GameManager::makeRound(std::istream& in, std::ostream& out) {
    if (_end_game) {
        return true;
    }
    for (auto & name : _names) {
        if (_players.find(name) == _players.end()) {
            continue;
        }
        out << "Turn: " << name << std::endl;
        _players[name]->getOpenedField()->printField(out);
        if (!_players[name]->isSkip()) {
            if (_players[name]->isTreasureKeeper()) {
                out << std::endl;
                std::cout << "You hold treasure" << std::endl;
                out << std::endl;
            }
            else if (_players[name]->isTreasureHold()) {
                out << std::endl;
                out << "!!!!!!!!!!!!ATTENTION!!!!!!!!!!!!" << std::endl;
                out << std::endl;
                std::cout << "Someone hold treasure" << std::endl;
                out << std::endl;
                out << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                out << std::endl;
            }
            Additional::operateTreasure(_players[name]->getPosition(), name, _players,
                                        _field, in, out, _hold_treasure);
            auto action_information = _players[name]->chooseAction(in, out);
            if (!_players[name]->isTreasureKeeper()) {
                _players[name]->setActionMode("shoot", true);
            }
            auto action = ActionFactory::Instance().getAction(action_information.first);
            action->doAction(name, _players, _field, action_information.second,
                             in, out, _hold_treasure, _end_game);
            if (_end_game) {
                return true;
            }
            if (_players.find(name) == _players.end()) {
                for (int i = 0; i < 25; i++) {
                    std::cout << std::endl;
                }
                continue;
            }
            _players[name]->getOpenedField()->printField(out);
            if (!_players[name]->isBot()) {
                std::string end_turn;
                std::cout << "Enter anything to end turn" << std::endl;
                std::cin >> end_turn;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            for (int i = 0; i < 25; i++) {
                std::cout << std::endl;
            }
        }
        else {
            if (!_players[name]->isBot()) {
                std::string end_turn;
                out << "You've been shot, so you need one turn to heal" << std::endl;
                std::cout << "Enter anything to end turn" << std::endl;
                std::cin >> end_turn;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            for (int i = 0; i < 25; i++) {
                std::cout << std::endl;
            }
            _players[name]->setSkipMode(false);
            _players[name]->setActionMode("shoot", true);
        }
        if (_end_game) {
            return true;
        }
    }
    return false;
}

const std::string &GameManager::getHoldTreasure() {
    return _hold_treasure;
}

std::shared_ptr<Field> GameManager::getField() {
    return _field;
}
