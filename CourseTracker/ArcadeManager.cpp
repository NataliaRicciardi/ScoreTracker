#include "ArcadeManager.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <cctype>

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