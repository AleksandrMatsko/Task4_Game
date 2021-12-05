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

    void ToLower(std::string& str) {
        for (int i = 0; i < str.size(); i++) {
            str[i] = char(std::tolower(str[i]));
        }
    }

    bool GetAnswer(std::istream& in, std::ostream& out) {
        out << "Please enter [yes] or [no] (without [])" << std::endl;
        std::string answer;
        while (true) {
            in >> answer;
            ToLower(answer);
            if (answer == "yes") {
                return true;
            }
            if (answer == "no") {
                return false;
            }
            out << "Please enter [yes] or [no] (without []):" << std::endl;
        }
    }
}

GameManager::GameManager(const std::list<std::string>& player_names) {
    _end_game = false;
    _field = std::make_shared<Field>();
    char i = '1';
    for (auto & player: player_names) {
        auto pos = GetStartPosition(i, _field);
        _players[player] = std::make_shared<Player>(pos, _field->getWidth(), _field->getHeight());
        _hold_treasure = "";
        i += 1;
    }
}

GameManager& GameManager::Instance(const std::list<std::string>& player_names) {
    static GameManager manager(player_names);
    return manager;
}

std::pair<int, int> GameManager::movePos(const std::pair<int, int>& pos, Direction direction) {
    auto new_pos = pos;
    if (direction == Direction::UP) {
        new_pos.first -= 1;
    }
    else if (direction == Direction::DOWN) {
        new_pos.first += 1;
    }
    else if (direction == Direction::LEFT) {
        new_pos.second -= 1;
    }
    else if (direction == Direction::RIGHT) {
        new_pos.second += 1;
    }
    return new_pos;
}

void GameManager::makeTurn(const std::string &player_name, const std::pair<std::string, Direction>& action, std::istream& in, std::ostream& out) {
    if (action.first == "move") {
        auto new_pos = _players[player_name]->getPosition();
        new_pos = movePos(new_pos, action.second);
        auto cell_sym = _field->viewCell(new_pos);
        auto cell = CellFactory::Instance().getCell(cell_sym);
        if (cell->canStand()) {
            if (cell->canInteract()) {
                char what = cell->getCellSym();
                if (what == 'T') {
                    out << "You found a treasure. Do you want to pick it up?" << std::endl;
                    out << "After picking up a treasure you can't shoot. What's your answer?" << std::endl;
                    bool answer = GetAnswer(in, out);
                    if (answer) {
                        _hold_treasure = player_name;
                        _players[player_name]->setShootMode(false);
                        _field->changeCell(new_pos, '0');
                    }

                }
                if (what == 'E') {
                    out << "You found an exit. Do you want to leave maze?" << std::endl;
                    out << "If you don't hold a treasure you will leave the game. What's your answer" << std::endl;
                    bool answer = GetAnswer(in, out);
                    if (answer && _hold_treasure != player_name) {
                        _players.erase(player_name);
                        return;
                    }
                    if (answer && _hold_treasure == player_name) {
                        _end_game = true;
                        return;
                    }
                    if (!answer) {
                        return;
                    }
                }
            }
            auto prev_pos = _players[player_name]->getPosition();
            auto opened_field = _players[player_name]->getOpenedField();
            opened_field->changeCell(prev_pos, _field->viewCell(prev_pos));
            opened_field->changeCell(new_pos, 'P');
            _players[player_name]->setPosition(new_pos);
        }
        else {
            out << "You find unpassable cell" << std::endl;
            auto opened_field = _players[player_name]->getOpenedField();
            opened_field->changeCell(new_pos, _field->viewCell(new_pos));
        }
    }
    if (action.first == "shoot") {
        auto bullet_pos = _players[player_name]->getPosition();
        auto cell_sym = _field->viewCell(bullet_pos);
        auto cell = CellFactory::Instance().getCell(cell_sym);
        bool anyone_shot = false;
        while (cell->canShootThrough()) {
            for (auto & player : _players) {
                if (player.first != player_name) {
                    auto pos = player.second->getPosition();
                    if (pos == bullet_pos) {
                        player.second->setShootMode(false);
                        player.second->setSkipMode(true);
                        anyone_shot = true;
                        if (player.first == _hold_treasure) {
                            _hold_treasure = "";
                            _field->changeCell(pos, 'T');
                        }
                    }
                }
            }
            bullet_pos = movePos(bullet_pos, action.second);
            cell_sym = _field->viewCell(bullet_pos);
            cell = CellFactory::Instance().getCell(cell_sym);
        }
        if (anyone_shot) {
            out << "You've shot somebody" << std::endl;
        }
        else {
            out << "You haven't shot anybody" << std::endl;
        }
    }
}

bool GameManager::makeRound(std::istream& in, std::ostream& out) {
    for (auto & player : _players) {
        out << "Turn: " << player.first << std::endl;
        player.second->getOpenedField()->printField(out);
        if (!player.second->canShoot() && player.first != _hold_treasure) {
            player.second->setShootMode(true);
        }
        if (!player.second->isSkip()) {
            auto action = player.second->chooseAction(in, out);
            makeTurn(player.first, action, in, out);
            player.second->getOpenedField()->printField(out);
        }
        else {
            out << "You've been shot" << std::endl;
            player.second->setSkipMode(false);
        }
        if (_end_game) {
            return false;
        }
    }
    return true;
}
