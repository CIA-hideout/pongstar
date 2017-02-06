#ifndef _MENU_H
#define _MENU_H

#include <vector>

#include "input.h"
#include "fontManager.h"
#include "scene.h"

namespace menuNS {
	const int TITLE_Y_POS = 140;
	const int MENU_Y_POS = 360;
	const int HEIGHT_BETWEEN_ITEM = 30;
	const int DIST_BTWN_MINUS_AND_ITEM = 20;
	const float BLINK_INTERVAL = 0.2f;
}

class Menu : public Scene {
private:
	// Game items
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
	Menu::Menu(Input* i, FontManager* fm);
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