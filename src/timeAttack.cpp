#include "timeAttack.h"

TimeAttack::TimeAttack(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) : 
PongstarBase(g, dm, fm, t) {}

TimeAttack::~TimeAttack() {}

void TimeAttack::update(float frameTime) {
	PongstarBase::update(frameTime);
}

void TimeAttack::render() {
	PongstarBase::render();

	std::string timeLeft = std::to_string((TIME_PER_GAME - elapsedTime) / 1000);

	fontManager->print(
		fontNS::SABO_FILLED,
		elapsedTime > 50 * 1000 ? fontNS::RED : fontNS::WHITE,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, timeLeft) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		timeLeft
		);
}
