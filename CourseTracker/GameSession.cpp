#include "GameSession.h"

GameSession::GameSession(std::string t, int s) : gameTitle(t), score(s) {}

std::string GameSession::getTitle() {
	return gameTitle;
}

int GameSession::getScore() {
	return score;
}