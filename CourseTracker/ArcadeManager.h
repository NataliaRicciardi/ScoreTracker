#pragma once

#include "Player.h"

#include <unordered_map>
#include <string>

class ArcadeManager {
private:
	std::unordered_map<std::string, Player> players;

public:
	void addPlayer(std::string name);
	void removePlayer(std::string name);
	void recordScore(std::string name, int score, std::string title, int duration);
	void displayAllPlayers();
	void removeAllPlayers();
	void showHighestScorer();
	void savePlayers();
	void loadPlayers();
};

