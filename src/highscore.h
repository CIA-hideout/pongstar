#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "scene.h"
#include "input.h"
#include "fontManager.h"
#include "dataManager.h"

namespace highScoreNS {
	const float SMALL_FONT_SIZE = 36.0;
	const float LARGE_FONT_SIZE = 48.0;

	const int OVERALL_Y_POS = 75;
	const int SIDEBAR_X_POS = 130;
	const int CLASSIC_Y_POS = 130;
	const int TIME_ATK_Y_POS = 200;

	const int ESC_X_POS = 170;
	const int ESC_Y_POS = 600;
	const int RANK_X_POS = 580;
	const int NAME_X_POS = 680;
	const int SCORE_RIGHT_X_POS = 1200;
	const int RANK_VERT_GAP = 10;

	const int BLINKER_GAP = 20;
	const float BLINK_INTERVAL = 0.2f;
}

class HighScore : public Scene {
private:
	Input* input;
	DataManager* dataManager;
	FontManager* baseFm;

	FontManager* largeFm;
	FontManager* smallFm;

	float blinkTimer;
	bool blink;

	void addHighScore();
	void renderClassicHS();
	void renderTimeAtkHS();

public:
	HighScore();
	HighScore(Input* i, DataManager* dm, FontManager* fm);
	~HighScore();

	// Interface
	void initialize(sceneNS::SceneData sd);
	void update(float frameTime);
	void ai() {};
	void collisions() {};
	void render();

	void releaseAll() {};
	void resetAll() {};
};

#endif