#pragma once

#include "GameSession.h"

#include <string>
#include <vector>
#include <map>

class Player {
private: 
	std::string name;
	std::vector<GameSession> gamesPlayed;

public:
	Player(std::string n);

	void addScore(int score, std::string title, int duration);
	std::string getName();
	std::map<std::string, float> getAverageScore();
	std::map<std::string, std::pair<int, int>> getTotalScore();
	void displayInfo();
	std::map<std::string, int> getHighestScores();
	std::vector<GameSession>& getGameSessions();
};

