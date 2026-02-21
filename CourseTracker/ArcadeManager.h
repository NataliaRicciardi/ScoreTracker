#pragma once

#include "Player.h"

#include <vector>
#include <string>

class ArcadeManager {
private:
	std::vector<Player> players;

public:
	void addPlayer(std::string name);
	void removePlayer(std::string name);
	void recordScore(std::string name, int score);
	void displayAllPlayers();
	void removeAllPlayers();
	void showHighestScorer();
	void savePlayers();
	void loadPlayers();
};

