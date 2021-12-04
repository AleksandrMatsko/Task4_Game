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
    _field = std::make_shared<Field>();
    char i = '1';
    for (auto & player: player_names) {
        auto pos = GetStartPosition(i, _field);
        _players[player] = std::make_shared<Player>(pos, _field->getWidth(), _field->getHeight());
        _hold_treasure = "";
        i += 1;
    }
}

void GameManager::makeTurn(const std::string &player_name, const std::pair<std::string, Direction>& action) {
    if (action.first == "move") {
        auto new_pos = _players[player_name]->getPosition();
        if (action.second == Direction::UP) {
            new_pos.first -= 1;
        }
        else if (action.second == Direction::DOWN) {
            new_pos.first += 1;
        }
        else if (action.second == Direction::LEFT) {
            new_pos.second -= 1;
        }
        else if (action.second == Direction::RIGHT) {
            new_pos.second += 1;
        }
        auto cell_sym = _field->viewCell(new_pos);
        auto cell = CellFactory::Instance().getCell(cell_sym);
        if (cell->canStand()) {
            auto prev_pos = _players[player_name]->getPosition();
            auto opened_field = _players[player_name]->getOpenedField();
            opened_field->changeCell(prev_pos, _field->viewCell(prev_pos));
            opened_field->changeCell(new_pos, 'P');
            _players[player_name]->setPosition(new_pos);
            //check treasure
            //message;
        }
        else {
            //check Exit
            //message
        }
    }
}

void GameManager::makeRound() {
    for (auto & player : _players) {
        if (!player.second->isSkip()) {
            auto action = player.second->chooseAction();
            GameManager::makeTurn(player.first, action);
        }
        else {
            player.second->setSkipMode(false);
        }
        if (!player.second->canShoot() && player.first != _hold_treasure) {
            player.second->setShootMode(true);
        }
    }
}