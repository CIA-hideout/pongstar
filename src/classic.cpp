#include "classic.h"

Classic::Classic(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) :
PongstarBase(g, dm, fm, t) {
	sceneType = sceneNS::CLASSIC;
}

Classic::~Classic() {}

void Classic::update(float frameTime) {
	PongstarBase::update(frameTime);

	int leftPaddleScore = entityManager->getPaddle(paddleNS::LEFT)->getScore();
	int rightPaddleScore = entityManager->getPaddle(paddleNS::RIGHT)->getScore();
	
	if (leftPaddleScore == pongstarNS::POINTS_TO_WIN || rightPaddleScore == pongstarNS::POINTS_TO_WIN) {
		nextSceneType = sceneNS::VICTORY;
		sceneData.gameMode = sceneNS::GM_CLASSIC;
		sceneData.winner = leftPaddleScore == pongstarNS::POINTS_TO_WIN ? sceneNS::W_LEFT : sceneNS::W_RIGHT;
		sceneData.newHighScore.score = elapsedTime;
	}
}