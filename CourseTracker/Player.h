#pragma once

#include <string>

class Player {
private: 
	std::string name;
	int totalScore;
	int gamesPlayed;

public:
	Player(std::string n);

	void addScore(int score);
	std::string getName();
	int getAverageScore();
	int getTotalScore();
	void displayInfo();
};

