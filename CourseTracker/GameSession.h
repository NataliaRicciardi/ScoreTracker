#pragma once
#include <string>

class GameSession {
	private:
		int score;
		std::string gameTitle;
		int durationMins;

	public:
		GameSession(int s, std::string t, int d);
		int getScore();
		std::string getGameTitle();
		int getDuration();
};

