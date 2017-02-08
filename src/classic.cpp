#include "classic.h"

Classic::Classic(Game* g, Audio* a, DataManager* dm, FontManager* fm, TextureManagerMap t) :
PongstarBase(g, a, dm, fm, t) {
	sceneType = sceneNS::CLASSIC;
	sceneData.gameMode = sceneNS::GM_CLASSIC;
}

Classic::~Classic() {}

void Classic::update(float frameTime) {
	PongstarBase::update(frameTime);

	int leftPaddleScore = entityManager->getPaddle(paddleNS::LEFT)->getScore();
	int rightPaddleScore = entityManager->getPaddle(paddleNS::RIGHT)->getScore();
	
	if (leftPaddleScore == pongstarNS::POINTS_TO_WIN || rightPaddleScore == pongstarNS::POINTS_TO_WIN) {
		nextSceneType = sceneNS::GAMEOVER;

		sceneData.scores.p1Score = leftPaddleScore;
		sceneData.scores.p2Score = rightPaddleScore;
		sceneData.scores.time = elapsedTime;
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