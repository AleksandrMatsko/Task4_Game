#include "PossibleActions.h"

namespace {
    bool RegisterActions() {
        ActionFactory::Instance().Register("move", actionMaker<Move>());
        ActionFactory::Instance().Register("shoot", actionMaker<Shoot>());
        return true;
    }

    static bool fake = RegisterActions();

    std::pair<int, int> movePos(const std::pair<int, int> &pos, Direction direction) {
        auto new_pos = pos;
        if (direction == Direction::UP) {
            new_pos.first -= 1;
        } else if (direction == Direction::DOWN) {
            new_pos.first += 1;
        } else if (direction == Direction::LEFT) {
            new_pos.second -= 1;
        } else if (direction == Direction::RIGHT) {
            new_pos.second += 1;
        }
        return new_pos;
    }
}

namespace Additional {
    void operateTreasure(std::pair<int, int> pos, const std::string& player_name,
                         std::map<std::string, std::shared_ptr<Player>>& players,
                         Field& field, std::istream& in, std::ostream& out,
                         std::string& hold_treasure) {
        auto cell_sym = field.viewCell(pos);
        auto cell = CellFactory::Instance().getCell(cell_sym);
        if (cell->getCellSym() == 'T') {
            if (!players[player_name]->isBot()) {
                Printer printer;
                printer.printTreasureFound(out);
            }
            bool answer = players[player_name]->getAnswer(in, out, 'T');
            if (answer) {
                hold_treasure = player_name;
                players[player_name]->setTreasureKeeper(true);
                for (auto & player : players) {
                    player.second->setTreasureHold(true);
                }
                players[player_name]->setActionMode("shoot", false);
                field.changeCell(pos, '0');
            }
        }
    }
}

bool Move::doAction(const std::string& player_name,
                    std::map<std::string, std::shared_ptr<Player>>& players,
                    Field& field, Direction direction, std::istream& in,
                    std::ostream& out, std::string& hold_treasure, bool& end_game) {
    Printer printer;
    auto new_pos = players[player_name]->getPosition();
    new_pos = movePos(new_pos, direction);
    auto cell_sym = field.viewCell(new_pos);
    auto cell = CellFactory::Instance().getCell(cell_sym);
    if (cell->canStand()) {
        if (cell->canInteract()) {
            char what = cell->getCellSym();
            if (what == 'E') {
                if (!players[player_name]->isBot()) {
                    printer.printExitFound(out);
                }
                bool answer = players[player_name]->getAnswer(in, out, 'E');
                if (answer && !players[player_name]->isTreasureKeeper()) {
                    players.erase(player_name);
                    if (players.empty()) {
                        end_game = true;
                    }
                    return true;
                }
                if (answer && players[player_name]->isTreasureKeeper()) {
                    end_game = true;
                    return true;
                }
                if (!answer) {
                    if (!players[player_name]->isBot()) {
                        players[player_name]->getOpenedField().changeCell(new_pos, what);
                    }
                    return false;
                }
                new_pos = players[player_name]->getPosition();
            }
        }
        Additional::operateTreasure(new_pos, player_name, players, field, in, out, hold_treasure);
        auto pos = players[player_name]->getPosition();
        players[player_name]->getOpenedField().changeCell(pos, field.viewCell(pos));
        players[player_name]->getOpenedField().changeCell(new_pos, 'P');
        players[player_name]->setPosition(new_pos);
        return true;
    }
    else {
        players[player_name]->getOpenedField().changeCell(new_pos, field.viewCell(new_pos));
        return false;
    }
}

bool Shoot::doAction(const std::string& player_name,
                     std::map<std::string, std::shared_ptr<Player>>& players,
                     Field& field, Direction direction, std::istream& in,
                     std::ostream& out, std::string& hold_treasure, bool& end_game) {
    auto bullet_pos = players[player_name]->getPosition();
    auto cell_sym = field.viewCell(bullet_pos);
    auto cell = CellFactory::Instance().getCell(cell_sym);
    bool anyone_shot = false;
    while (cell->canShootThrough()) {
        for (auto & player : players) {
            if (player.first == player_name) {
                continue;
            }
            auto pos = player.second->getPosition();
            if (pos == bullet_pos) {
                player.second->setActionMode("shoot", false);
                player.second->setSkipMode(true);
                anyone_shot = true;
                if (player.second->isTreasureKeeper()) {
                    hold_treasure = "";
                    player.second->setTreasureKeeper(false);
                    for (auto & player : players) {
                        player.second->setTreasureHold(false);
                    }
                    field.changeCell(pos, 'T');
                }
            }
        }
        bullet_pos = movePos(bullet_pos, direction);
        cell_sym = field.viewCell(bullet_pos);
        cell = CellFactory::Instance().getCell(cell_sym);
    }
    players[player_name]->setActionMode("shoot", false);
    Additional::operateTreasure(players[player_name]->getPosition(), player_name, players, field, in, out,
                                hold_treasure);
    return anyone_shot;
}