#include "timeAttack.h"

TimeAttack::TimeAttack(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) : 
PongstarBase(g, dm, fm, t) {}

TimeAttack::~TimeAttack() {}

void TimeAttack::update(float frameTime) {
	PongstarBase::update(frameTime);

	Input* input = game->getInput();

	if (input->wasKeyPressed(SPACE_KEY) && !timeStarted) {
		startTime = steady_clock::now();
		timeStarted = true;
	}

	if (timeStarted) {
		steady_clock::time_point presentTime = steady_clock::now();
		elapsedTime = duration_cast<seconds>(presentTime - startTime).count();
	}
}

void TimeAttack::render() {
	PongstarBase::render();

	std::string timeLeft = std::to_string(TIME_PER_GAME - elapsedTime);

	fontManager->print(
		fontNS::SABO_FILLED,
		elapsedTime > 50 ? fontNS::RED : fontNS::WHITE,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, timeLeft) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		timeLeft
		);
}
