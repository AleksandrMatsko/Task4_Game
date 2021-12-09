#include "GameManager.h"

int main() {
    std::cout << rules;
    std::string input;
    int num_players;
    while (true) {
        std::cout << "Please enter number of players (from 1 to 4):" << std::endl;
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
    std::list<std::string> player_names;
    for (int i = 0; i < num_players; i++) {
        std::cout << "Please enter the name of " << i + 1 << " player" << std::endl;
        std::getline(std::cin, input);
        bool is_unique = true;
        for (auto & name : player_names) {
            if (name == input) {
                i -= 1;
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            player_names.emplace_back(input);
        }
        else  {
            std::cout << "Name already entered" << std::endl;
        }
    }
    bool end_game = false;
    while (!end_game) {
        end_game = GameManager::Instance(player_names).makeRound(std::cin, std::cout);
    }
    std::string winner = GameManager::Instance(player_names).getHoldTreasure();
    std::cout << std::endl;
    if (winner.empty()) {
        std::cout << "Nobody win" << std::endl;
    }
    else {
        std::cout << "!!!  Winner: " << winner << "  !!!" << std::endl;
    }
    std::cout << std::endl;
    GameManager::Instance(player_names).getField()->printField(std::cout);
    return 0;
}