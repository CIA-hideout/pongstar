#ifndef _CREDITS_H
#define _CREDITS_H

#include <vector>

#include "scene.h"
#include "input.h"
#include "fontManager.h"

namespace creditsNS {
	const float SMALL_FONT_SIZE = 36.0;
	const float MEDIUM_FONT_SIZE = 48.0;
	const float LARGE_FONT_SIZE = 60.0;

	const int TITLE_Y_POS = 70;
	const int SUBTITLE_Y_POS = 220;
	const int ORANGE_DASH_Y_POS = 280;
	const int DEVELOPERS_Y_POS = 318;
	const int BLUE_DASH_Y_POS = 454;
	const int ESC_Y_POS = 614;

	const int BLINKER_GAP = 20;
	const float BLINK_INTERVAL = 0.2f;
}

class Credits : public Scene {
private:
	Input* input;
	FontManager* baseFm;

	FontManager* largeFm;
	FontManager* mediumFm;
	FontManager* smallFm;

	float blinkTimer;
	bool blink;

public:
	Credits();
	Credits(Input* i, FontManager* fm);
	~Credits();

	void initialize(sceneNS::SceneData sd);
	void update(float frameTime);
	void ai() {};
	void collisions() {};
	void render();

	void releaseAll() {};
	void resetAll() {};
};

#endif