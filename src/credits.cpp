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

	largeFm = new FontManager(*baseFm);
	mediumFm = new FontManager(*baseFm);
	smallFm = new FontManager(*baseFm);

	float scale = creditsNS::LARGE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	largeFm->setScale(fontNS::SABO_FILLED, scale);
	largeFm->setScale(fontNS::SABO, scale);
	largeFm->setKerning(fontNS::SABO_FILLED, 15);
	largeFm->setKerning(fontNS::SABO, 15);

	scale = creditsNS::MEDIUM_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	mediumFm->setScale(fontNS::SABO_FILLED, scale);
	mediumFm->setScale(fontNS::SABO, scale);

	scale = creditsNS::SMALL_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	smallFm->setScale(fontNS::SABO_FILLED, scale);
	smallFm->setScale(fontNS::SABO, scale);

	sceneData.escToMenu = true;
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
	int titleXpos = GAME_WIDTH / 2 - largeFm->getTotalWidth(fontNS::SABO_FILLED, "CREDITS") / 2;
	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::RED,
		titleXpos,
		creditsNS::TITLE_Y_POS,
		"CREDITS"
	);

	int subtitleXpos = GAME_WIDTH / 2 - smallFm->getTotalWidth(fontNS::SABO_FILLED, "DEVELOPED BY") / 2;
	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::GREY,
		subtitleXpos,
		creditsNS::SUBTITLE_Y_POS,
		"DEVELOPED BY"
	);

	int dashXpos = GAME_WIDTH / 2 - mediumFm->getTotalWidth(fontNS::SABO, "-") / 2;
	mediumFm->print(
		fontNS::SABO,
		fontNS::ORANGE,
		dashXpos,
		creditsNS::ORANGE_DASH_Y_POS,
		"-"
	);
	mediumFm->print(
		fontNS::SABO,
		fontNS::BLUE,
		dashXpos,
		creditsNS::BLUE_DASH_Y_POS,
		"-"
	);

	int nameXpos = GAME_WIDTH / 2 - mediumFm->getTotalWidth(fontNS::SABO_FILLED, "IVAN") / 2;
	int nameYpos = creditsNS::DEVELOPERS_Y_POS;
	mediumFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		nameXpos,
		nameYpos,
		"IVAN"
	);

	nameXpos = GAME_WIDTH / 2 - mediumFm->getTotalWidth(fontNS::SABO_FILLED, "JEROME") / 2;
	nameYpos = creditsNS::DEVELOPERS_Y_POS + (mediumFm->getHeight(fontNS::SABO_FILLED) * 1);
	mediumFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		nameXpos,
		nameYpos,
		"JEROME"
	);

	nameXpos = GAME_WIDTH / 2 - mediumFm->getTotalWidth(fontNS::SABO_FILLED, "CHESTER") / 2;
	nameYpos = creditsNS::DEVELOPERS_Y_POS + (mediumFm->getHeight(fontNS::SABO_FILLED) * 2);
	mediumFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		nameXpos,
		nameYpos,
		"CHESTER"
	);

	int escWidth = smallFm->getTotalWidth(fontNS::SABO_FILLED, "PRESS ESC");
	int escXpos = GAME_WIDTH / 2 - escWidth / 2;

	if (blink) {
		smallFm->print(
			fontNS::SABO,
			fontNS::ORANGE,
			escXpos - smallFm->getTotalWidth(fontNS::SABO, "-") - creditsNS::BLINKER_GAP,
			creditsNS::ESC_Y_POS,
			"-"
		);

		smallFm->print(
			fontNS::SABO,
			fontNS::BLUE,
			escXpos + escWidth + creditsNS::BLINKER_GAP,
			creditsNS::ESC_Y_POS,
			"-"
		);
	}

	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		escXpos,
		creditsNS::ESC_Y_POS,
		"PRESS ESC"
	);
}

