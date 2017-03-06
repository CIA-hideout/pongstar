#include "gameover.h"

Gameover::Gameover() {}

Gameover::Gameover(Game* g, Audio* a, FontManager* fm) {
	sceneType = sceneNS::GAMEOVER;
	game = g;
	audio = a;
	baseFm = fm;
	input = game->getInput();
}

Gameover::~Gameover() {}

void Gameover::initialize(sceneNS::SceneData sd) {
	sceneData = sd;

	if (sceneData.playMenuCue) {
		audio->stopCue(GAME_CUE);
		audio->playCue(MENU_CUE);
	}

	sceneData.playMenuCue = false;
	sceneData.playGameCue = false;

	blink = true;
	input->clearTextIn();

	largeFm = new FontManager(*baseFm);
	smallFm = new FontManager(*baseFm);

	float scale = gameoverNS::LARGE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	largeFm->setScale(fontNS::SABO_FILLED, scale);
	largeFm->setScale(fontNS::SABO, scale);

	scale = gameoverNS::SMALL_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	smallFm->setScale(fontNS::SABO_FILLED, scale);
	smallFm->setScale(fontNS::SABO, scale);

	if (!gameoverTexture.initialize(game->getGraphics(), GAMEOVER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover texture"));

	if (!gameover.initialize(game->getGraphics(), 0, 0, 0, &gameoverTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover"));

	D3DXCreateLine(game->getGraphics()->get3Ddevice(), &topLine);
	topLine->SetWidth(gameoverNS::TB_LINE_HEIGHT);

	D3DXCreateLine(game->getGraphics()->get3Ddevice(), &bottomLine);
	bottomLine->SetWidth(gameoverNS::TB_LINE_HEIGHT);

	D3DXCreateLine(game->getGraphics()->get3Ddevice(), &cursor);
	cursor->SetWidth(gameoverNS::CURSOR_LINE_WIDTH);
}

void Gameover::update(float frameTime) {
	if (input->wasKeyPressed(ENTER_KEY)) {
		if (sceneData.scores.p1Score != sceneData.scores.p2Score) {
			if (input->getTextIn().length()) {
				nextSceneType = sceneNS::HIGH_SCORES;
				sceneData.scores.name = toUpperCase(input->getTextIn());
			}
		} else {
			nextSceneType = sceneNS::MENU;
		}

		input->clearTextIn();
	}

	if (blinkTimer < gameoverNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}
	else {
		blink = !blink;
		blinkTimer = 0.0;
	}
}

void Gameover::renderScore() {
	if (sceneData.gameMode == sceneNS::GM_CLASSIC) {
		// Classic mode: display time
		fontNS::FONT_COLOR winnerColor = (sceneData.scores.p1Score > sceneData.scores.p2Score) ?
			fontNS::ORANGE : fontNS::BLUE;

		int wholeTime = sceneData.scores.time / 1000;			// get first 2 digit for seconds
		int decimalTime = sceneData.scores.time % 1000 / 10;	// get first 2 digit after conversion to decimal

		char timeStr[512];
		sprintf_s(timeStr, "%i.%02i", wholeTime, decimalTime);

		int timeWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, timeStr);

		largeFm->print(
			fontNS::SABO_FILLED,
			winnerColor,
			GAME_WIDTH / 2 - timeWidth / 2 - fontNS::CENTER_OFFSET,
			gameoverNS::SCORE_Y_POS,
			timeStr
		);
	} else {
		// Time Attack mode: display both scores
		int dashWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, "-");
		int dashXpos = GAME_WIDTH / 2 - dashWidth / 2 - fontNS::CENTER_OFFSET;

		std::string p1ScoreStr = std::to_string(sceneData.scores.p1Score);
		std::string p2ScoreStr = std::to_string(sceneData.scores.p2Score);
		int p1ScoreWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, p1ScoreStr);

		largeFm->print(
			fontNS::SABO_FILLED,
			fontNS::ORANGE,
			dashXpos - gameoverNS::SCORE_DASH_GAP - p1ScoreWidth,
			gameoverNS::SCORE_Y_POS,
			p1ScoreStr
		);

		largeFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE,
			dashXpos,
			gameoverNS::SCORE_Y_POS,
			"-"
		);

		largeFm->print(
			fontNS::SABO_FILLED,
			fontNS::BLUE,
			dashXpos + dashWidth + gameoverNS::SCORE_DASH_GAP,
			gameoverNS::SCORE_Y_POS,
			p2ScoreStr
		);
	}
}

void Gameover::renderDraw() {
	// Render blue line
	VECTOR2 topLinePoints[gameoverNS::TB_POINTS_COUNT] = { gameoverNS::TOP_LINE_LEFT, gameoverNS::TOP_LINE_RIGHT };

	topLine->Begin();
	topLine->Draw(topLinePoints, gameoverNS::TB_POINTS_COUNT, graphicsNS::BLUE);
	topLine->End();

	// Render "DRAW"
	int drawWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, "DRAW");
	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		GAME_WIDTH / 2 - drawWidth / 2 - fontNS::CENTER_OFFSET,
		gameoverNS::INPUT_Y_POS,
		"DRAW"
	);

	// Render orange line
	VECTOR2 bottomLinePoints[gameoverNS::TB_POINTS_COUNT] = { gameoverNS::BOTTOM_LINE_LEFT, gameoverNS::BOTTOM_LINE_RIGHT };

	bottomLine->Begin();
	bottomLine->Draw(bottomLinePoints, gameoverNS::TB_POINTS_COUNT, graphicsNS::ORANGE);
	bottomLine->End();
}

void Gameover::renderTextbox() {
	// Render "ENTER YOUR NAME"
	std::string prompt = "ENTER YOUR NAME";
	int promptWidth = smallFm->getTotalWidth(fontNS::SABO_FILLED, prompt);

	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::GREY,
		GAME_WIDTH / 2 - promptWidth / 2 - fontNS::CENTER_OFFSET,
		gameoverNS::PROMPT_Y_POS,
		prompt
	);

	COLOR_ARGB winnerColor = (sceneData.scores.p1Score > sceneData.scores.p2Score) ?
		graphicsNS::ORANGE : graphicsNS::BLUE;

	// Render textbox line
	VECTOR2 tbPoints[gameoverNS::TB_POINTS_COUNT] = { gameoverNS::BOTTOM_LINE_LEFT, gameoverNS::BOTTOM_LINE_RIGHT };

	bottomLine->Begin();
	bottomLine->Draw(tbPoints, gameoverNS::TB_POINTS_COUNT, winnerColor);
	bottomLine->End();

	// Render input text
	std::string tbValue = toUpperCase(input->getTextIn());
	int totalWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);

	while (totalWidth > gameoverNS::TB_WIDTH - gameoverNS::TB_SIDE_PADDING * 2) {
		// Only display text within textbox width
		tbValue.erase(tbValue.begin());
		totalWidth = largeFm->getTotalWidth(fontNS::SABO_FILLED, tbValue);
	}

	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		GAME_WIDTH / 2 - totalWidth / 2 - fontNS::CENTER_OFFSET,
		gameoverNS::INPUT_Y_POS,
		tbValue
	);

	// Render cursor
	if (blink) {
		int cursorXpos = (GAME_WIDTH / 2 - (int)gameoverNS::CURSOR_LINE_WIDTH / 2) + totalWidth / 2 + gameoverNS::CURSOR_SIDE_PADDING;

		VECTOR2 cursorTop = VECTOR2((float)cursorXpos, gameoverNS::CURSOR_Y_POS);
		VECTOR2 cursorBottom = VECTOR2((float)cursorXpos, gameoverNS::CURSOR_Y_POS + gameoverNS::CURSOR_HEIGHT);
		VECTOR2 cursorPoints[gameoverNS::CURSOR_POINTS_COUNT] = { cursorTop, cursorBottom };

		cursor->Begin();
		cursor->Draw(cursorPoints, gameoverNS::CURSOR_POINTS_COUNT, graphicsNS::WHITE);
		cursor->End();
	}
}

void Gameover::render() {
	gameover.draw();

	renderScore();
	(sceneData.scores.p1Score == sceneData.scores.p2Score) ? renderDraw() : renderTextbox();

	int textWidth = smallFm->getTotalWidth(fontNS::SABO_FILLED, "PRESS ENTER");
	int textXpos = GAME_WIDTH / 2 - textWidth / 2;

	if (blink) {
		smallFm->print(
			fontNS::SABO,
			fontNS::ORANGE,
			textXpos - smallFm->getTotalWidth(fontNS::SABO, "-") - gameoverNS::BLINKER_GAP,
			gameoverNS::ENTER_Y_POS,
			"-"
		);

		smallFm->print(
			fontNS::SABO,
			fontNS::BLUE,
			textXpos + textWidth + gameoverNS::BLINKER_GAP,
			gameoverNS::ENTER_Y_POS,
			"-"
		);
	}

	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		textXpos,
		gameoverNS::ENTER_Y_POS,
		"PRESS ENTER"
	);
}

void Gameover::releaseAll() {
	gameoverTexture.onLostDevice();
	topLine->OnLostDevice();
	bottomLine->OnLostDevice();
	cursor->OnLostDevice();
}

void Gameover::resetAll() {
	gameoverTexture.onResetDevice();
	topLine->OnResetDevice();
	bottomLine->OnResetDevice();
	cursor->OnResetDevice();
}	
