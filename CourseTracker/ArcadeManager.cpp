#include "ArcadeManager.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <filesystem>

static void toUpper(std::string& input) {
	for (auto& c : input) {
		c = std::toupper(c);
	}
}

static int yesOrNo(std::string& input) {
	toUpper(input);

	if (input == "NO") {
		return 1;
	}
	else if (input == "YES") {
		return 2;
	}
	else {
		return 3;
	}
}

void ArcadeManager::addPlayer(std::string name) {
	toUpper(name);
	
	for (auto& player : players) {
		if (player.getName() == name) {
			std::cout << "A player with this name already exists.\n";
			return;
		}
	}

	Player newP(name);
	players.push_back(newP);
	std::cout << "New Player Created!\n";
}

void ArcadeManager::removePlayer(std::string name) {
	std::string input;
	bool invalid;
	
	toUpper(name);
	for (int i = 0; i < players.size(); i++) {
		if (players[i].getName() == name) {

			do {
				invalid = false;
				std::cout << "Are you sure you want to remove this player? (yes to remove, no to cancel): ";
				std::cin >> input;

				int response = yesOrNo(input);

				if (response == 1) {
					std::cout << "Player removal canceled.\n";
					return;
				}
				else if (response == 2) {
					continue;
				}
				else {
					std::cout << "Invalid Input.\n";
					invalid = true;
				}
			} while (invalid);


			players.erase(players.begin() + i);
			std::cout << "Player erased successfully.\n";
			return;
		}
	}

	std::cout << "Player not found.\n";
}

void ArcadeManager::recordScore(std::string name, int score) {
	toUpper(name);
	
	if (score <= 0) {
		std::cout << "Invalid Score: Zero or Negative.\n";
	}
	
	for (auto& player : players) {
		if (player.getName() == name) {
			player.addScore(score);
			std::cout << "Score Added Successfully!\n";
			return;
		}
	}
	
	std::cout << "Player not found.\n";
}

void ArcadeManager::displayAllPlayers() {
	if (players.size() == 0) {
		std::cout << "There are no players yet!\n";
		return;
	}

	for (auto& player : players) {
		player.displayInfo();
	}
}

void ArcadeManager::removeAllPlayers() {
	std::string input;
	bool invalid;

	do {
		invalid = false;
		std::cout << "Are you sure you want to remove all players? (yes to remove, no to cancel): ";
		std::cin >> input;
		
		int response = yesOrNo(input);

		if (response == 1) {
			std::cout << "Player removal canceled.\n";
			return;
		}
		else if (response == 2) {
			players.clear();
			std::cout << "Removed all players.\n";
			return;
		}
		else {
			std::cout << "Invalid Input.\n";
			invalid = true;
		}
	} while (invalid);
}

void ArcadeManager::showHighestScorer() {
	if (players.empty()) {
		std::cout << "There is no highest score yet!\n";
		return;
	}

	Player best = players[0];

	for (auto& player : players) {
		if (player.getTotalScore() > best.getTotalScore()) {
			best = player;
		}
	}

	std::cout << "Highest score is " << best.getTotalScore() << " by player " << best.getName() << "!\n";
}

void ArcadeManager::savePlayers() {
	std::ofstream file("savedata/playerSave.txt");
	if (file.is_open()) {

		file << "Name" << "," << "Score" << "\n";
		
		for (auto& player : players) {
			
			std::vector<GameSession> sessions = player.getGameSessions();

			if (sessions.size() == 0) {
				file << player.getName() << "," << 0;
				continue;
			}
			
			for (auto& session : sessions) {
				file << player.getName() << "," << session.getScore() << "\n";
			}
		}

		file.close();

		std::cout << "Scores Saved Successfully!\n";
	}
	else {
		std::cout << "Opening file failed.\n";
	}
}

void ArcadeManager::loadPlayers() {
	bool load;
	std::string input;
	bool invalid;

	do {
		invalid = false;
		std::cout << "Do you want to load your previous session? (yes or no): ";
		std::cin >> input;

		int response = yesOrNo(input);

		if (response == 1) {
			std::cout << "Previous session will be overwrote when you choose 'exit'.\n";
			return;
		}
		else if (response == 2) {
			std::cout << "Previous session loading... YOU NEED TO \"EXIT\" TO SAVE YOUR CHANGES!\n";
			load = true;
		}
		else {
			std::cout << "Invalid Input.\n";
			invalid = true;
		}

	} while (invalid);

	try {
		namespace fs = std::filesystem;
		if (!fs::exists("savedata/playerSave.txt") || fs::is_empty("savedata/playerSave.txt")) {
			std::cout << "There is no info from a previous session to load!\n";
			return;
		}
	}
	catch (...) {
		std::cout << "There was an error with the file.";
		return;
	}

	
	if (load) {
		std::ifstream file("savedata/playerSave.txt"); // open for read
		
		if (!file.is_open()) {
			std::cout << "Opening file failed.\n";
			return;
		}
		
		std::string line;

		// skip header
		std::getline(file, line);

		while (std::getline(file, line)) {
			std::stringstream ss(line); // for splitting
			std::string name;
			std::string scoreStr;
			int score;

			bool createPlayer = true;

			if (std::getline(ss, name, ',') && std::getline(ss, scoreStr, ',')) {
				try {
					score = stoi(scoreStr);
				}
				catch (...) {
					std::cout << "Invalid score for player (CSV)" << name << "\n";
					continue;
				}
				
				createPlayer = true;

				for (auto & player : players) {
					if (player.getName() == name) {
						createPlayer = false;
						
						if (score != 0) player.addScore(score);
						
						continue;
					}
				}

				if (createPlayer) {
					Player newP(name);

					if (score != 0) newP.addScore(score);

					players.push_back(newP);
				}

			}
		}

		file.close();
	}
}
