#ifndef _GAMEOVER_H
#define _GAMEOVER_H

#include "util/util.h"
#include "game.h"
#include "scene.h"
#include "input.h"
#include "fontManager.h"
#include "textureManager.h"

namespace gameoverNS {
	const int SCORE_Y_POS = 200;
	const int SCORE_DASH_GAP = 20;
	const float LARGE_FONT_SIZE = 60.0;
	const float SMALL_FONT_SIZE = 36.0;

	const int ENTER_Y_POS = 600;
	const int BLINKER_GAP = 20;
	const float BLINK_INTERVAL = 0.2f;

	const int PROMPT_Y_POS = 330;

	const int TB_WIDTH = 400;
	const int TB_LINE_X_POS = 440;
	const int TB_POINTS_COUNT = 2;
	const int TB_SIDE_PADDING = 10;
	const float TB_LINE_HEIGHT = 5.0;

	const int TOP_LINE_Y_POS = 405;
	const VECTOR2 TOP_LINE_LEFT = VECTOR2((float)TB_LINE_X_POS, (float)TOP_LINE_Y_POS);
	const VECTOR2 TOP_LINE_RIGHT = VECTOR2((float)(TB_LINE_X_POS + TB_WIDTH), (float)TOP_LINE_Y_POS);

	const int BOTTOM_LINE_Y_POS = 465;
	const VECTOR2 BOTTOM_LINE_LEFT = VECTOR2((float)TB_LINE_X_POS, (float)BOTTOM_LINE_Y_POS);
	const VECTOR2 BOTTOM_LINE_RIGHT = VECTOR2((float)(TB_LINE_X_POS + TB_WIDTH), (float)BOTTOM_LINE_Y_POS);

	const int INPUT_Y_POS = 405;
	const float CURSOR_Y_POS = 415.0;
	const float CURSOR_HEIGHT = 42.0;
	const int CURSOR_SIDE_PADDING = 5;
	const int CURSOR_POINTS_COUNT = 2;
	const float CURSOR_LINE_WIDTH = 3.0;
}

class Gameover : public Scene {
private:
	Game* game;
	Audio* audio;
	Input* input;
	FontManager* baseFm;

	Image gameover;
	TextureManager gameoverTexture;

	FontManager* largeFm;
	FontManager* smallFm;

	float blinkTimer;
	bool blink;

	LP_LINE topLine;
	LP_LINE bottomLine;
	LP_LINE cursor;

	void renderDraw();
	void renderScore();
	void renderTextbox();

public:
	Gameover();
	Gameover(Game* g, Audio* a, FontManager* fm);
	~Gameover();

	// Interface
	void initialize(sceneNS::SceneData sd);
	void update(float frameTime);
	void ai() {};
	void collisions() {};
	void render();

	void releaseAll();
	void resetAll();
};

#endif