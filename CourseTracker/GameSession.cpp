#include "GameSession.h"

GameSession::GameSession(int s, std::string t, int d) : score(s), gameTitle(t), durationMins(d) {}

int GameSession::getScore() {
	return score;
}

std::string GameSession::getGameTitle() {
	return gameTitle;
}

int GameSession::getDuration() {
	return durationMins;
}