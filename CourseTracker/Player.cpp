#include "Player.h"

#include <iostream>
#include <format>

Player::Player(std::string n): name(n), totalScore(0), gamesPlayed(0) {} // shorthand

void Player::addScore(int score) {
	totalScore += score;
	gamesPlayed++;
}

int Player::getAverageScore() {
	if (gamesPlayed == 0) return 0;

	return totalScore / gamesPlayed;
}

std::string Player::getName() {
	return name;
}

int Player::getTotalScore() {
	return totalScore;
}

void Player::displayInfo() {
	std::cout << std::format("Name: {}\nTotal Score: {}\nGames Played: {}\nAverage Score: {}\n\n", name, totalScore, gamesPlayed, getAverageScore());
}