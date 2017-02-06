#include "victory.h"

Victory::Victory() {}

Victory::Victory(Graphics* g, Input* i, FontManager* fm) {
	sceneType = sceneNS::VICTORY;

	graphics = g;
	input = i;
	baseFm = fm;
}

Victory::~Victory() {}

void Victory::initialize(sceneNS::SceneData sd) {
	sceneData = sd;
	input->clearTextIn();

	titleFm = new FontManager(*baseFm);
	titleFm->setScale(fontNS::SABO_FILLED, 1.0f);

	D3DXCreateLine(graphics->get3Ddevice(), &textBox);
	textBox->SetWidth(victoryNS::tbLineWidth);

	D3DXCreateLine(graphics->get3Ddevice(), &cursor);
	cursor->SetWidth(victoryNS::cursorLineWidth);
}

void Victory::update(float frameTime) {
	if (input->wasKeyPressed(ENTER_KEY)) {
		if (sceneData.winner != sceneNS::W_DRAW) {
			nextSceneType = sceneNS::HIGH_SCORES;
			sceneData.newHighScore.name = toUpperCase(input->getTextIn());
			sceneData.hsDisplayMode = sceneData.modePlayed == sceneNS::GM_CLASSIC ? sceneNS::HS_CLASSIC : sceneNS::HS_TIME_ATK;
		} else {
			nextSceneType = sceneNS::MENU;
		}

		input->clearTextIn();
	}
}

void Victory::renderTxb() {
	// Draw the textbox
	VECTOR2 tbPoints[victoryNS::tbPointsToDraw] = { victoryNS::tbTopLeft, victoryNS::tbTopRight,
		victoryNS::tbBottomRight, victoryNS::tbBottomLeft, victoryNS::tbTopLeft };

	textBox->Begin();
	textBox->Draw(tbPoints, victoryNS::tbPointsToDraw, graphicsNS::WHITE);
	textBox->End();

	// Determine if text fits tb
	std::string tbValue = toUpperCase(input->getTextIn());
	int totalWidth = baseFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);

	while (totalWidth > victoryNS::tbWidth - victoryNS::tbPadding * 2) {
		// remove text from front to fit tb
		tbValue.erase(tbValue.begin());
		totalWidth = baseFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);
	}

	baseFm->print(fontNS::SABO_FILLED, fontNS::WHITE, victoryNS::textStartX, victoryNS::textStartY, tbValue);

	// Draw cursor after getting width of text
	VECTOR2 cursorTop = victoryNS::cursorStartTop + VECTOR2(totalWidth + victoryNS::cursorPadding, 0);
	VECTOR2 cursorBottom = victoryNS::cursorStartBottom + VECTOR2(totalWidth + victoryNS::cursorPadding, 0);
	VECTOR2 cursorPoints[victoryNS::cursorPointsToDraw] = { cursorTop, cursorBottom };

	cursor->Begin();
	cursor->Draw(cursorPoints, victoryNS::cursorPointsToDraw, graphicsNS::WHITE);
	cursor->End();
}

void Victory::render() {
	if (sceneData.winner == sceneNS::W_DRAW) {
		titleFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE,
			GAME_WIDTH / 2 - titleFm->getTotalWidth(fontNS::SABO_FILLED, "DRAW") / 2 - fontNS::CENTER_OFFSET_MAX_SCALE,
			victoryNS::drawStartY,
			"DRAW"
			);
	} else {
		renderTxb();

		char winnerStr[512];
		fontNS::FONT_COLOR color = sceneData.winner == sceneNS::W_LEFT ? fontNS::ORANGE : fontNS::BLUE;
		sprintf(winnerStr, "%s WON THE GAME", sceneData.winner == sceneNS::W_RIGHT ? "ORANGE" : "BLUE");

		std::string enterYourNameStr = "ENTER YOUR NAME:";

		baseFm->print(
			fontNS::SABO_FILLED, 
			color, 
			GAME_WIDTH / 2 - baseFm->getTotalWidth(fontNS::SABO_FILLED, winnerStr) / 2 - fontNS::CENTER_OFFSET,
			victoryNS::winnerStrStartY, 
			winnerStr
			);

		baseFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE, 
			GAME_WIDTH / 2 - baseFm->getTotalWidth(fontNS::SABO_FILLED, enterYourNameStr) / 2 - fontNS::CENTER_OFFSET,
			victoryNS::enterYourNameStartY, 
			enterYourNameStr
		);
	}

	std::string enterToContinueStr = "PRESS ENTER TO CONTINUE";
	baseFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		GAME_WIDTH / 2 - baseFm->getTotalWidth(fontNS::SABO_FILLED, enterToContinueStr) / 2 - fontNS::CENTER_OFFSET,
		victoryNS::enterToContinueStartY,
		enterToContinueStr
		);
}

void Victory::releaseAll() {
	textBox->OnLostDevice();
}

void Victory::resetAll() {
	textBox->OnResetDevice();
}	
