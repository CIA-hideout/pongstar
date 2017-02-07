#include "credits.h"

Credits::Credits() {}

Credits::Credits(Input* i, FontManager* fm) {
	sceneType = sceneNS::CREDITS;

	input = i;
	baseFm = fm;
}

Credits::~Credits() {}

void Credits::initialize(sceneNS::SceneData sd) {
	blink = true;

	/*largeFm = new FontManager(*baseFm);
	mediumFm = new FontManager(*baseFm);
	smallFm = new FontManager(*baseFm);*/

	//float scale = creditsNS::LARGE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	//largeFm->setScale(fontNS::SABO_FILLED, scale);
	//largeFm->setScale(fontNS::SABO, scale);
	//largeFm->setKerning(fontNS::SABO_FILLED, 15);
	//largeFm->setKerning(fontNS::SABO, 15);

	//scale = creditsNS::MEDIUM_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	//mediumFm->setScale(fontNS::SABO_FILLED, scale);
	//mediumFm->setScale(fontNS::SABO, scale);

	//scale = creditsNS::SMALL_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	//smallFm->setScale(fontNS::SABO_FILLED, scale);
	//smallFm->setScale(fontNS::SABO, scale);
}

void Credits::update(float frameTime) {
	if (blinkTimer < creditsNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}
	else {
		blink = !blink;
		blinkTimer = 0.0;
	}
}

void Credits::render() {
	/*int titleXpos = GAME_WIDTH / 2 - largeFm->getTotalWidth(fontNS::SABO_FILLED, "CREDITS") / 2;
	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::RED,
		titleXpos,
		creditsNS::TITLE_Y_POS,
		"CREDITS"
	);*/
}

