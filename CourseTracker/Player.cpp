#include "Player.h"

#include <iostream>
#include <format>
#include <numeric>


Player::Player(std::string n): name(n) {} // shorthand

void Player::addScore(int score) {
	GameSession game(score);
	gamesPlayed.push_back(game);
}

int Player::getAverageScore() {
	int size = gamesPlayed.size();

	if (size == 0) {
		return 0;
	}
	
	return getTotalScore() / size;
}

std::string Player::getName() {
	return name;
}

int Player::getTotalScore() {
	return std::accumulate(gamesPlayed.begin(), gamesPlayed.end(), 0, 
		[](int sum, GameSession& game) {
			return sum + game.getScore();
		}
	);
}

void Player::displayInfo() {
	std::cout << std::format("Name: {}\nTotal Score: {}\nGames Played: {}\nAverage Score: {}\n\n", name, getTotalScore(), gamesPlayed.size(), getAverageScore());
}