#ifndef _MENU_H
#define _MENU_H

#include <vector>

#include "scene.h"
#include "audio.h"
#include "input.h"
#include "fontManager.h"

namespace menuNS {
	const int TITLE_Y_POS = 140;
	const float TITLE_FONT_SIZE = 96.0;
	const int MENU_Y_POS = 360;
	const float MENU_FONT_SIZE = 48.0;
	const int MENU_VERT_GAP = 30;
	const int BLINKER_GAP = 20;
	const float BLINK_INTERVAL = 0.2f;
}

class Menu : public Scene {
private:
	// Game items
	Audio* audio;
	Input* input;
	FontManager* baseFm;

	// Scene items
	FontManager* titleFm;
	FontManager* menuFm;
	std::vector<sceneNS::TYPE> items;
	int selectedItemIndex;

	float blinkTimer;
	bool blink;

public:
	Menu();
	Menu::Menu(Audio* a, Input* i, FontManager* fm);
	~Menu();

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
