#include "GameManager.h"

namespace {
    std::pair<int, int> GetStartPosition(const char num_player, Field& f) {
        auto field = f.getField();
        auto height = f.getHeight();
        auto width = f.getWidth();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (field[i * width + j] == num_player) {
                    auto pos = std::make_pair(i, j);
                    f.changeCell(pos, '0');
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
    _field = GeneralField();
    auto all_actions = ActionFactory::Instance().getAllActions();
    char max_num_players = 4;
    std::vector<char> numbers = {'1', '2', '3', '4'};
    for (auto & player: _names) {
        char index = rand() % max_num_players;
        auto pos = GetStartPosition(numbers[index], _field);
        _players[player] = std::make_shared<HumanPlayer>(pos, all_actions);
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
        _players[bot_name] = std::make_shared<Bot>(pos, all_actions);
    }
}

bool GameManager::makeRound(std::istream& in, std::ostream& out) {
    if (_end_game) {
        return true;
    }
    Printer printer;
    for (auto & name : _names) {
        if (_players.find(name) == _players.end()) {
            continue;
        }
        printer.printWhoseTurn(out, name);
        printer.printField(out, _players[name]->getOpenedField());
        if (!_players[name]->isSkip()) {
            printer.printTreasureInformation(out, _players[name]->isTreasureKeeper(), _players[name]->isTreasureHold());
            Additional::operateTreasure(_players[name]->getPosition(), name, _players,
                                        _field, in, out, _hold_treasure);
            auto action_information = _players[name]->chooseAction(in, out);
            if (!_players[name]->isTreasureKeeper()) {
                _players[name]->setActionMode("shoot", true);
            }
            auto action = ActionFactory::Instance().getAction(action_information.first);
            if (_players[name]->isBot()) {
                printer.printAction(out, action_information.first, action_information.second);
            }
            bool is_success = action->doAction(name, _players, _field, action_information.second,
                                            in, out, _hold_treasure, _end_game);
            printer.printIsActionSuccess(out, action_information.first, is_success);
            if (_end_game) {
                return true;
            }
            if (_players.find(name) == _players.end()) {
                for (int i = 0; i < 25; i++) {
                    std::cout << std::endl;
                }
                continue;
            }
            printer.printField(out, _players[name]->getOpenedField());
        }
        else {
            printer.printWasShot(out);
            _players[name]->setSkipMode(false);
            _players[name]->setActionMode("shoot", true);
        }
        printer.printEndTurn(out);
        _players[name]->endTurn(in, out);
        if (_end_game) {
            return true;
        }
    }
    return false;
}

const std::string &GameManager::getHoldTreasure() {
    return _hold_treasure;
}

GeneralField& GameManager::getField() {
    return _field;
}
