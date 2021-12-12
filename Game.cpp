#include "Game.h"

Game::Game(std::istream &in, std::ostream &out) {
    Printer printer;
    printer.printRules(std::cout);
    std::string input;
    int num_players;
    while (true) {
        printer.printChoiceNumberPlayers(std::cout);
        std::cin >> input;
        if (input.find_first_not_of("01234567890") == std::string::npos) {
            num_players = std::stoi(input);
            if (num_players < 0 || num_players > 4) {
                continue;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    for (int i = 0; i < num_players; i++) {
        printer.printChoiceName(std::cout, i + 1);
        std::getline(std::cin, input);
        bool is_unique = true;
        for (auto & name : _player_names) {
            if (name == input) {
                i -= 1;
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            _player_names.emplace_back(input);
        }
        else  {
            printer.printNameOccupied(std::cout);
        }
    }
}

void Game::start(std::istream &in, std::ostream &out) {
    Printer printer;
    GameManager manager(_player_names);
    bool end_game = false;
    while (!end_game) {
        end_game = manager.makeRound(std::cin, std::cout);
    }
    printer.printWinner(std::cout, manager.getHoldTreasure());
    printer.printField(std::cout, manager.getField());
}