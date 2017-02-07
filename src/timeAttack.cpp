#include "timeAttack.h"

TimeAttack::TimeAttack(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) : 
PongstarBase(g, dm, fm, t) {
	sceneType = sceneNS::TIME_ATK;
	sceneData.gameMode = sceneNS::GM_TIME_ATK;
}

TimeAttack::~TimeAttack() {}

void TimeAttack::update(float frameTime) {
	PongstarBase::update(frameTime);

	int leftPaddleScore = entityManager->getPaddle(paddleNS::LEFT)->getScore();
	int rightPaddleScore = entityManager->getPaddle(paddleNS::RIGHT)->getScore();

	if (elapsedTime >= pongstarNS::TIME_PER_GAME) {
		nextSceneType = sceneNS::GAMEOVER;

		sceneData.scores.p1Score = leftPaddleScore;
		sceneData.scores.p2Score = rightPaddleScore;
	}
}

void TimeAttack::render() {
	PongstarBase::render();

	std::string timeLeft = std::to_string((pongstarNS::TIME_PER_GAME - elapsedTime) / 1000);

	fontManager->print(
		fontNS::SABO_FILLED,
		elapsedTime > (pongstarNS::TIME_PER_GAME - pongstarNS::TEN_SECONDS) ? fontNS::RED : fontNS::WHITE,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, timeLeft) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		timeLeft
	);
}
