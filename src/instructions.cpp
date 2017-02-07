#include "instructions.h"

Instructions::Instructions() {}

Instructions::Instructions(Game* g, FontManager* fm) {
	sceneType = sceneNS::INSTRUCTIONS;
	game = g;
	baseFm = fm;
}

Instructions::~Instructions() {}

void Instructions::initialize(sceneNS::SceneData sd) {
	blink = true;

	titleFm = new FontManager(*baseFm);
	textFm = new FontManager(*baseFm);
	gameMode = sd.gameMode;

	if (!instructionsTexture.initialize(game->getGraphics(), INSTRUCTIONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions texture"));

	if (!instructions.initialize(game->getGraphics(), 0, 0, 0, &instructionsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions"));
}

void Instructions::update(float frameTime) {
	Input* input = game->getInput();

	if (input->wasKeyPressed(SPACE_KEY)) {
		if (gameMode == sceneNS::GM_CLASSIC) {
			nextSceneType = sceneNS::CLASSIC;
		}
		else {
			nextSceneType = sceneNS::TIME_ATK;
		}
	}

	if (blinkTimer < instructionsNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}
	else {
		blink = !blink;
		blinkTimer = 0.0;
	}
}

void Instructions::render() {
	instructions.draw();

	if (gameMode == sceneNS::GM_CLASSIC) {
		renderTitle("ELEVEN", "POINTS");
	}
	else {
		renderTitle("SIXTY", "SECONDS");
	}

	float scale = instructionsNS::TEXT_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	textFm->setScale(fontNS::SABO_FILLED, scale);
	textFm->setScale(fontNS::SABO, scale);

	int textWidth = textFm->getTotalWidth(fontNS::SABO_FILLED, "PRESS SPACE");
	int textXpos = GAME_WIDTH / 2 - textWidth / 2;

	if (blink) {
		textFm->print(
			fontNS::SABO,
			fontNS::ORANGE,
			textXpos - textFm->getTotalWidth(fontNS::SABO, "-") - instructionsNS::BLINKER_GAP,
			instructionsNS::TEXT_Y_POS,
			"-"
		);

		textFm->print(
			fontNS::SABO,
			fontNS::BLUE,
			textXpos + textWidth + instructionsNS::BLINKER_GAP,
			instructionsNS::TEXT_Y_POS,
			"-"
		);
	}

	textFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		textXpos,
		instructionsNS::TEXT_Y_POS,
		"PRESS SPACE"
	);
}

void Instructions::renderTitle(std::string firstWord, std::string secondWord) {
	float scale = instructionsNS::TITLE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	titleFm->setScale(fontNS::SABO_FILLED, scale);
	titleFm->setScale(fontNS::SABO, scale);
	titleFm->setKerning(fontNS::SABO_FILLED, 15);
	titleFm->setKerning(fontNS::SABO, 15);

	int titleWidth = titleFm->getTotalWidth(fontNS::SABO, firstWord) + titleFm->getTotalWidth(fontNS::SABO, secondWord);
	int titleXpos = GAME_WIDTH / 2 - titleWidth / 2 - fontNS::CENTER_OFFSET;

	titleFm->print(
		fontNS::SABO,
		fontNS::WHITE,
		titleXpos,
		instructionsNS::TITLE_Y_POS,
		firstWord
	);

	titleFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		titleXpos + titleFm->getTotalWidth(fontNS::SABO_FILLED, firstWord),
		instructionsNS::TITLE_Y_POS,
		secondWord
	);
}

void Instructions::releaseAll() {
	instructionsTexture.onLostDevice();
}

void Instructions::resetAll() {
	instructionsTexture.onResetDevice();
}
