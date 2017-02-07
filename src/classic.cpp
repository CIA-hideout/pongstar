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

void Classic::render() {
	PongstarBase::render();

	std::string stopwatch = std::to_string(elapsedTime / 1000);

	fontManager->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, stopwatch) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		stopwatch
	);
}