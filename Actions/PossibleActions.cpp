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
        bool GetAnswer(std::istream& in, std::ostream& out) {
        out << "Please enter [yes] or [no] (without [])" << std::endl;
        std::string answer;
        while (true) {
            in >> answer;
            StrModifier::ToLower(answer);
            if (answer == "yes") {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
            if (answer == "no") {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
            out << "Please enter [yes] or [no] (without []):" << std::endl;
        }
    }

    void operateTreasure(std::pair<int, int> pos, const std::string& player_name,
                         std::map<std::string, std::shared_ptr<Player>>& players,
                         std::shared_ptr<Field>& field, std::istream& in, std::ostream& out,
                         std::string& hold_treasure) {
        auto cell_sym = field->viewCell(pos);
        auto cell = CellFactory::Instance().getCell(cell_sym);
        if (cell->getCellSym() == 'T') {
            out << "You found a treasure. Do you want to pick it up?" << std::endl;
            out << "After picking up a treasure you can't shoot. What's your answer?" << std::endl;
            bool answer = GetAnswer(in, out);
            if (answer) {
                hold_treasure = player_name;
                players[player_name]->setActionMode("shoot", false);
                field->changeCell(pos, '0');
            }
        }
    }
}

bool Move::doAction(const std::string& player_name,
                    std::map<std::string, std::shared_ptr<Player>>& players,
                    std::shared_ptr<Field>& field, Direction direction, std::istream& in,
                    std::ostream& out, std::string& hold_treasure, bool& end_game) {
    auto new_pos = players[player_name]->getPosition();
    new_pos = movePos(new_pos, direction);
    auto cell_sym = field->viewCell(new_pos);
    auto cell = CellFactory::Instance().getCell(cell_sym);
    if (cell->canStand()) {
        if (cell->canInteract()) {
            char what = cell->getCellSym();
            if (what == 'E') {
                out << "You found an exit. Do you want to leave maze?" << std::endl;
                out << "If you don't hold a treasure you will leave the game. What's your answer" << std::endl;
                bool answer = Additional::GetAnswer(in, out);
                if (answer && hold_treasure != player_name) {
                    players.erase(player_name);
                    if (players.empty()) {
                        end_game = true;
                    }
                    return true;
                }
                if (answer && hold_treasure == player_name) {
                    end_game = true;
                    return true;
                }
                if (!answer) {
                    return false;
                }
            }
        }
        Additional::operateTreasure(new_pos, player_name, players, field, in, out, hold_treasure);
        auto pos = players[player_name]->getPosition();
        auto open_field = players[player_name]->getOpenedField();
        open_field->changeCell(pos, field->viewCell(pos));
        open_field->changeCell(new_pos, 'P');
        players[player_name]->setPosition(new_pos);
        return true;
    }
    else {
        out << "You find unpassable cell" << std::endl;
        auto opened_field = players[player_name]->getOpenedField();
        opened_field->changeCell(new_pos, field->viewCell(new_pos));
        return false;
    }
}

bool Shoot::doAction(const std::string& player_name,
                     std::map<std::string, std::shared_ptr<Player>>& players,
                     std::shared_ptr<Field>& field, Direction direction, std::istream& in,
                     std::ostream& out, std::string& hold_treasure, bool& end_game) {
    auto bullet_pos = players[player_name]->getPosition();
    auto cell_sym = field->viewCell(bullet_pos);
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
                if (player.first == hold_treasure) {
                    hold_treasure = "";
                    field->changeCell(pos, 'T');
                }
            }
        }
        bullet_pos = movePos(bullet_pos, direction);
        cell_sym = field->viewCell(bullet_pos);
        cell = CellFactory::Instance().getCell(cell_sym);
    }
    if (anyone_shot) {
        out << std::endl;
        out << "=================================" << std::endl;
        out << std::endl;
        out << "You've shot somebody" << std::endl;
        out << std::endl;
        out << "=================================" << std::endl;
        out << std::endl;
    }
    else {
        out << std::endl;
        out << "=================================" << std::endl;
        out << std::endl;
        out << "You haven't shot anybody" << std::endl;
        out << std::endl;
        out << "=================================" << std::endl;
        out << std::endl;
    }
    players[player_name]->setActionMode("shoot", false);
    Additional::operateTreasure(players[player_name]->getPosition(), player_name, players, field, in, out,
                                hold_treasure);
    return anyone_shot;
}