#include "ArcadeManager.h"
#include "Player.h"

#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_map>
#include <format>

static void toUpper(std::string& input) {
	for (auto& c : input) {
		c = std::toupper(static_cast<unsigned char>(c));
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
	
	if (players.contains(name)) {
		std::cout << "A player with this name already exists.\n";
		return;
	}

	players.emplace(name, Player(name));
	std::cout << "New Player Created!\n";
}

void ArcadeManager::removePlayer(std::string name) {
	std::string input;
	bool invalid;
	
	toUpper(name);

	if (players.contains(name)) {
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


		players.erase(name);
		std::cout << "Player erased successfully.\n";
		return;
	}
	else {
		std::cout << "Player not found.\n";
		return;
	}

}

void ArcadeManager::recordScore(std::string name, int score, std::string title, int duration) {
	toUpper(name);
	toUpper(title);
	
	auto it = players.find(name);

	if (it != players.end()) {
		it->second.addScore(score, title, duration);
		std::cout << "Score Added Successfully!\n";
	}
	else {
		std::cout << "Player not found.\n";
		return;
	}
}

void ArcadeManager::displayAllPlayers() {
	if (players.empty()) {
		std::cout << "There are no players yet!\n";
		return;
	}

	for (auto& pair : players) {
		pair.second.displayInfo();
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
		std::cout << "There are no players yet!\n";
		return;
	}
	
	// gamename, playername, score
	std::map<std::string, std::pair<std::string, int>> allHighest;
	
	for (auto& pair : players) {
		// gamename, score
		std::map<std::string, int> highestScores = pair.second.getHighestScores(); // get each player's highest scores

		for (auto& score : highestScores) { //iterate over the player's scores and check if any of theirs are greater than pre-saved values
			auto it = allHighest.find(score.first);

			if (it != allHighest.end()) {
				if (it->second.second < score.second) {
					it->second.first = pair.first;
					it->second.second = score.second;
				}
			}
			else {
				allHighest.emplace(score.first, std::make_pair(pair.first, score.second));
			}
		}
	}

	if (allHighest.empty()) {
		std::cout << "There are no saved scores yet!\n";
		return;
	}

	for (auto& score : allHighest) {
		std::cout << std::format("\nHighest for {}: {} got a score of {}!\n", score.first, score.second.first, score.second.second);
	}
}

void ArcadeManager::savePlayers() {
	std::ofstream file("savedata/playerSave.txt");
	if (file.is_open()) {

		file << "Name," << "Score" << "," << "Title" << "," << "Duration" << "\n";
		
		for (auto& pair : players) {
			
			std::vector<GameSession> sessions = pair.second.getGameSessions();

			if (sessions.size() == 0) {
				file << pair.second.getName() << ",null\n";
				continue;
			}
			
			for (auto& session : sessions) {
				file << pair.second.getName() << "," << session.getScore() << "," << session.getGameTitle() << "," << session.getDuration() << "\n";
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
	bool load = false;
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
			std::string title;
			std::string durationStr;
			int duration;


			if (std::getline(ss, name, ',') && std::getline(ss, scoreStr, ',')) {
				
				toUpper(name);

				if (scoreStr != "null") {
					
					std::getline(ss, title, ',');
					std::getline(ss, durationStr, ',');
					
					try {
						score = stoi(scoreStr);
						duration = stoi(durationStr);
					}
					catch (...) {
						std::cout << "Invalid score for player (CSV)" << name << "\n";
						continue;
					}

					auto it = players.find(name);

					if (it != players.end()) {
						it->second.addScore(score, title, duration);
					}
					else {
						Player newP(name);

						newP.addScore(score, title, duration);

						players.emplace(name, newP);
					}
				}
				else {
					auto it = players.find(name);

					if (it == players.end()) {
						players.emplace(name, Player(name));
					}
				}

			}
		}

		file.close();
	}
}

void ArcadeManager::playerStats(std::string name) {
	if (players.empty()) {
		std::cout << "There are no players yet!\n";
		return;
	}

	toUpper(name);

	auto it = players.find(name);
	if (it != players.end()) {
		// total games played
		std::cout << "Total games played: " << it->second.getGameSessions().size() << "\n";

		// total game scores
		std::map<std::string, std::pair<int, int>> totals = it->second.getTotalScore();

		std::cout << "Total Game Scores: \n";
		for (auto& total : totals) {
			std::cout << std::format("    {}: {}\n", total.first, total.second.first);
		}

		// average game scores
		std::map<std::string, float> averages = it->second.getAverageScore();
		
		std::cout << "Average Game Scores: \n";
		for (auto& average : averages) {
			std::cout << std::format("    {}: {}\n", average.first, average.second);
		}

		// highest game scores
		std::map<std::string, int> scores = it->second.getHighestScores();

		std::cout << "Highest Game Scores: \n";
		for (auto& score : scores) {
			std::cout << std::format("    {}: {}\n", score.first, score.second);
		}

		// total time played
		std::cout << std::format("Total Time Played: {} minutes\n", it->second.totalTime());

	}
	else {
		std::cout << "Could not find player " << name << ".\n";
		return;
	}

}

void ArcadeManager::gameBoard(std::string title) {
	if (players.empty()) {
		std::cout << "There are no players yet! Add some players and games to make a leaderboard!\n";
		return;
	}

	toUpper(title);

	// playername, score for ordering highest
	std::vector<std::pair<std::string, int>> leaderboard;
	
	for (auto& player : players) {
		// gamename, score
		std::map<std::string, int> highestScores = player.second.getHighestScores();

		for (auto& score : highestScores) {

			if (score.first == title) { // only add to leaderboard if the game title is right
				leaderboard.push_back({ player.first, score.second });
			}
		}
	}

	if (leaderboard.empty()) {
		std::cout << "There are no scores yet for this game! \n";
		return;
	}
	
	
	// sort vector leaderboard by the score
	std::sort(leaderboard.begin(), leaderboard.end(),
		[](auto& a, auto& b) {
			return a.second > b.second;
		}
	);

	int index = 1;
	for (auto& score : leaderboard) {
		std::cout << std::format("\nRank {}: {} {}\n", index, score.first, score.second);
		index++;
	}
}

void ArcadeManager::mostActivePlayer() {
	if (players.empty()) {
		std::cout << "No players yet!\n";
	}
	
	// playernames, value (more than one playername if they are equal stats)
	std::pair<std::vector<std::string>, int> mostGames;
	std::pair<std::vector<std::string>, int> longTime;
	bool init = false;

	for (auto& pair : players) {
		int numsessions = pair.second.getGameSessions().size();
		
		if (numsessions > mostGames.second) {
			
			mostGames.first.clear(); // empty list if numgames is bigger
			mostGames.first.push_back(pair.first);
			mostGames.second = numsessions;

			init = true;
		}
		else if (numsessions == mostGames.second) {
			mostGames.first.push_back(pair.first); // add to list if games is equal
		}

		int timeplayed = pair.second.totalTime();

		if (timeplayed > longTime.second) {
			
			longTime.first.clear();
			longTime.first.push_back(pair.first);
			longTime.second = timeplayed;

			init = true;
		}
		else if (timeplayed == longTime.second) {
			longTime.first.push_back(pair.first); // add to list if timeplayed is equal
		}
	}
	
	if (init) {
		std::cout << "\nMost Active by Most Games Played: \n";
		
		if (mostGames.first.size() == 1) {
			std::cout << std::format("    Player {} with {} total games played!\n", mostGames.first[0], mostGames.second);
		}
		else {
			for (int i = 0; i < mostGames.first.size(); i++) {
				if (i == 0) {
					std::cout << "    Player " << mostGames.first[i];
				}
				else if (i > 0 && i < mostGames.first.size() - 1) {
					std::cout << ", Player " << mostGames.first[i];
				}
				else {
					std::cout << " and Player " << mostGames.first[i];
				}
			}

			std::cout << std::format(" with {} total games played!\n", mostGames.second);
		}
		
		std::cout << "\nMost Active by Longest Total Time Played: \n";
		
		if (longTime.first.size() == 1) {
			std::cout << std::format("    Player {} with {} total minutes played!\n", longTime.first[0], longTime.second);
		}
		else {
			for (int i = 0; i < longTime.first.size(); i++) {
				if (i == 0) {
					std::cout << "    Player " << longTime.first[i];
				}
				else if (i > 0 && i < longTime.first.size() - 1) {
					std::cout << ", Player " << longTime.first[i];
				}
				else {
					std::cout << " and Player " << longTime.first[i];
				}
			}
			std::cout << std::format(" with {} total minutes played!\n", longTime.second);
		}
	}
	else {
		std::cout << "No sessions found!\n";
	}

}

void ArcadeManager::totalPlaytime(std::string name) {

}

void ArcadeManager::popularGame() {

}