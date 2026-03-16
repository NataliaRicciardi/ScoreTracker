#include "Player.h"

#include <iostream>
#include <format>
#include <numeric>
#include <map>


Player::Player(std::string n): name(n) {} // shorthand

void Player::addScore(int score, std::string title, int duration) {
	GameSession game(score, title, duration);
	gamesPlayed.push_back(game);
}

std::map<std::string, float> Player::getAverageScore() {
	std::map<std::string, std::pair<int, int>> totals = getTotalScore();
	std::map<std::string, float> averages;

	for (auto& pair : totals) {
		averages.emplace(pair.first, ((float) pair.second.first / pair.second.second));
	}

	return averages;
}

std::string Player::getName() {
	return name;
}

std::map<std::string, std::pair<int, int>> Player::getTotalScore() {
	
	// gameTitle, score, count
	std::map<std::string, std::pair<int, int>> totals;
	
	for (auto& game : gamesPlayed) {
		auto it = totals.find(game.getGameTitle());

		if (it != totals.end()) {
			it->second.first += game.getScore();
			it->second.second++;
		}
		else {
			totals.emplace(game.getGameTitle(), std::make_pair(game.getScore(), 1));
		}
	}

	return totals;
	
}

std::map<std::string, int> Player::getHighestScores() {

	std::map<std::string, int> scores;
	
	for (auto& game : gamesPlayed) {
		auto it = scores.find(game.getGameTitle());

		if (it != scores.end()) {
			int gameScore = game.getScore();
			
			if (it->second < gameScore) {
				it->second = gameScore;
			}
		}
		else {
			scores.emplace(game.getGameTitle(), game.getScore());
		}
	}

	return scores;
}

void Player::displayInfo() {
	std::cout << std::format("\nName: {}\nTotal Scores: \n", name);

	std::map<std::string, std::pair<int, int>> totals = getTotalScore();

	for (auto& pair : totals) {
		std::cout << std::format("    Title: {}\n    Total Score: {}\n", pair.first, pair.second.first);
	}

	std::cout << std::format("Games Played: {}\n", gamesPlayed.size());

	for (auto& game : gamesPlayed) {
		std::cout << std::format("    Title: {}\n    Score: {}\n    Duration: {} minutes\n\n", game.getGameTitle(), game.getScore(), game.getDuration());
	}

	std::cout << "Average Scores: \n";

	std::map<std::string, float> averages = getAverageScore();

	for (auto& pair : averages) {
		std::cout << std::format("    Title: {}\n    Average: {}\n", pair.first, pair.second);
	}

}

std::vector<GameSession>& Player::getGameSessions() {
	return gamesPlayed;
}

int Player::totalTime() {
	if (gamesPlayed.empty()) {
		return 0;
	}
	
	return std::accumulate(gamesPlayed.begin(), gamesPlayed.end(), 0, 
		[](int sum, GameSession& game) {
			return sum + game.getDuration();
		}
	);
}

std::string Player::removeScore(int score, std::string title, int duration) {
	if (gamesPlayed.empty()) {
		return "No Scores";
	}

	for (int i = 0; i < gamesPlayed.size() - 1; i++) {
		if (gamesPlayed[i].getScore() == score && gamesPlayed[i].getGameTitle() == title && gamesPlayed[i].getDuration() == duration) {
			gamesPlayed.erase(gamesPlayed.begin() + i);

			return "Success";
		}
	}

	return "Not Found";
}