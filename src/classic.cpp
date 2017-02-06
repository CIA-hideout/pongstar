#include "classic.h"

Classic::Classic(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) :
PongstarBase(g, dm, fm, t) {}

Classic::~Classic() {}

void Classic::update(float frameTime) {
	PongstarBase::update(frameTime);

	paddleNS::SIDE winner;
	bool winnerFound = false;
	int leftPaddleScore = messageManager->getPaddle(paddleNS::LEFT)->getScore();
	int rightPaddleScore = messageManager->getPaddle(paddleNS::RIGHT)->getScore();
	
	if (leftPaddleScore == classicNS::POINTS_TO_WIN || rightPaddleScore == classicNS::POINTS_TO_WIN)
		winnerFound = true;
	
	if (winnerFound) {
		nextSceneType = sceneNS::VICTORY;
		sceneData.modePlayed = sceneNS::GM_CLASSIC;
		sceneData.winner = leftPaddleScore == classicNS::POINTS_TO_WIN ? sceneNS::W_LEFT : sceneNS::W_RIGHT;
		sceneData.newHighScore.score = elapsedTime;
	}
}