#pragma once

#include "GameSession.h"

#include <string>
#include <vector>

class Player {
private: 
	std::string name;
	std::vector<GameSession> gamesPlayed;

public:
	Player(std::string n);

	void addScore(int score);
	std::string getName();
	int getAverageScore();
	int getTotalScore();
	void displayInfo();
	std::vector<GameSession> getGameSessions();
};

