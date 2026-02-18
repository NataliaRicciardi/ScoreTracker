#include <iostream>
#include "ArcadeManager.h"

int main() {
    ArcadeManager manager;

    std::cout << "------------------- Arcade Manager -------------------\n\n";

    bool running = true;
    bool error = false;
    std::string input;
    int choice;
    while (running) {
        std::cout << "\n1. Add Player\n2. Remove a Player\n3. Record Score\n4. Show Players\n5. Remove All Players\n6. Show Highest Score\n7. Exit\n";
        
        do {
            error = false;
            std::cout << "\nEnter an action here: ";
            std::cin >> input;

            try {
                choice = std::stoi(input);

                if (choice > 7 || choice < 1) {
                    throw (choice);
                }
            }
            catch (int choice) {
                std::cout << "Input out of range.\n";
                error = true;
            }
            catch (const std::exception& e) {
                std::cout << "Invalid Input.\n";
                error = true;
            }
        } while (error);

        std::string name;
        std::string score;
        int scoreI;
        switch (choice) {
            case 1:
                std::cout << "Enter Player Name: ";
                std::getline(std::cin >> std::ws, name);

                manager.addPlayer(name);
                break;

            case 2:
                std::cout << "Enter Player Name for Removal: ";
                std::getline(std::cin >> std::ws, name);

                manager.removePlayer(name);
                break;

            case 3:
                std::cout << "Enter Player Name: ";
                std::getline(std::cin >> std::ws, name);

                error = false;
                do {
                    std::cout << "Enter Player Score: ";
                    std::cin >> score;
                    try {
                        scoreI = stoi(score);
                    }
                    catch (const std::exception& e) {
                        std::cout << "Invalid Input. Try Again.\n";
                        error = true;
                    }
                } while (error);

                manager.recordScore(name, scoreI);
                break;


            case 4:
                manager.displayAllPlayers();
                break;

            case 5: 
                manager.removeAllPlayers();
                break;

            case 6:
                manager.showHighestScorer();
                break;

            case 7:
                running = false;
                break;
        }

    }
}
