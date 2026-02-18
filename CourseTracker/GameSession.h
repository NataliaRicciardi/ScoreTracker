#pragma once
#include <string>

class GameSession {
	private:
		std::string gameTitle;
		int score;

	public:
		GameSession(std::string t, int s);
		std::string getTitle();
		int getScore();
};

