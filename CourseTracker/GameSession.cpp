#include "GameSession.h"

GameSession::GameSession(int s) : score(s) {}

int GameSession::getScore() {
	return score;
}