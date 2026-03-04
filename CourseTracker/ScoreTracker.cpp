#include <iostream>
#include "ArcadeManager.h"

int main() {
    ArcadeManager manager;

    std::cout << "------------------- Arcade Manager -------------------\n\n";

    manager.loadPlayers();
    
    bool running = true;
    bool error = false;
    std::string input;
    int choice;
    while (running) {
        std::cout << "\n1. Add Player\n2. Remove a Player\n3. Record Score\n4. Show Players\n5. Remove All Players\n6. Show Highest Scores\n" << 
            "7. Show Player Statistics\n8. Game Leaderboards\n9. Most Active Player\n10. Total Playtime per Player\n11. Most Played Game\n12. Exit\n";
        
        do {
            error = false;
            std::cout << "\nEnter an action here: ";
            std::cin >> input;

            try {
                choice = std::stoi(input);

                if (choice > 12 || choice < 1) {
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
        std::string gameTitle;
        std::string durationS;
        int durationI;

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

                std::cout << "Enter Game Title: ";
                std::getline(std::cin >> std::ws, gameTitle);

                do {
                    error = false;
                    std::cout << "Enter Player Score: ";
                    std::cin >> score;
                    try {
                        scoreI = stoi(score);

                        if (scoreI < 0) {
                            std::cout << "Invalid Input: Zero or Negative.\n";
                            error = true;
                        }
                    }
                    catch (const std::exception&) {
                        std::cout << "Invalid Score Input. Try Again.\n";
                        error = true;
                    }
                } while (error);

                do {
                    error = false;
                    std::cout << "Enter Duration (minutes): ";
                    std::cin >> durationS;
                    try {
                        durationI = stoi(durationS);

                        if (durationI <= 0) {
                            std::cout << "Invalid Input: Zero or Negative.\n";
                            error = true;
                        }
                    }
                    catch (const std::exception&) {
                        std::cout << "Invalid Duration Input. Try Again\n";
                        error = true;
                    }
                } while (error);

                manager.recordScore(name, scoreI, gameTitle, durationI);
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
                std::cout << "Enter Player Name: ";
                std::getline(std::cin >> std::ws, name);
                
                manager.playerStats(name);
                break;

                //total games played, total score per game, average score per game, highest score per game, total time played

            case 8: 
                std::cout << "Enter Game Title: ";
                std::getline(std::cin >> std::ws, gameTitle);
                
                manager.gameBoard(gameTitle);
                break;
                
                // rank 1, rank 2, ... highest scores by title

            case 9: 
                manager.mostActivePlayer();
                break;
                
                // by most sessions played and total duration

            case 10: 
                std::cout << "Enter Player Name: ";
                std::getline(std::cin >> std::ws, name);
                
                manager.totalPlaytime(name);
                break;
                
                // total playtime
                // per player

            case 11: 
                manager.popularGame();
                break;
                
                // Most played game
                // compare sessions per game title across all players

            case 12:
                manager.savePlayers();
                running = false;
                break;
        }

    }
}
