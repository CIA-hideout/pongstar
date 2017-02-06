#ifndef _VICTORY_H
#define _VICTORY_H

#include "util/util.h"
#include "graphics.h"
#include "input.h"
#include "fontManager.h"
#include "scene.h"

namespace victoryNS {
	const int gameCenterX = GAME_WIDTH / 2;
	const int tbWidth = 600;
	const int tbHeight = 70;
	const int tbStartX = gameCenterX - tbWidth / 2;
	const int tbStartY = 300;
	const int tbLineWidth = 5;
	const int tbPointsToDraw = 4 + 1; // need draw a line connecting the last point to the first

	const VECTOR2 tbTopLeft = VECTOR2(tbStartX, tbStartY);
	const VECTOR2 tbTopRight = VECTOR2(gameCenterX + tbWidth / 2, tbStartY);		
	const VECTOR2 tbBottomLeft = VECTOR2(tbStartX, tbStartY + tbHeight);
	const VECTOR2 tbBottomRight = VECTOR2(gameCenterX + tbWidth / 2, tbStartY + tbHeight);

	const int cursorLineWidth = 3;
	const int cursorPointsToDraw = 2;
	const int tbPadding = 8 + tbLineWidth;
	const int cursorPadding = 5;
	const VECTOR2 cursorStartTop = VECTOR2(tbStartX + tbPadding, tbStartY + tbPadding);
	const VECTOR2 cursorStartBottom = VECTOR2(tbStartX + tbPadding, tbStartY + tbHeight - tbPadding);

	// no need padding because font autopads
	const int textStartX = tbStartX;
	const int textStartY = tbStartY;

	const int winnerStrStartY = 70;
	const int enterYourNameStartY = 230;
	const int enterToContinueStartY = 550;
	const int drawStartY = 200;
}

class Victory : public Scene {
private:
	Graphics* graphics;
	Input* input;
	FontManager* baseFm;

	FontManager* titleFm;

	LP_LINE textBox;
	LP_LINE cursor;

	void renderTxb();
public:
	Victory();
	Victory(Graphics* g, Input* i, FontManager* fm);
	~Victory();

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