#ifndef _MENU_H
#define _MENU_H

#include <vector>

#include "constants.h"
#include "graphics.h"
#include "input.h"
#include "fontManager.h"

namespace menuNS {
	const int TITLE_Y_POS = 70;
	const int MENU_Y_POS = 250;
	const int HEIGHT_BETWEEN_ITEM = 90;
	const int DIST_BTWN_MINUS_AND_ITEM = 20;
	const float BLINK_INTERVAL = 0.2f;

	enum SCENE_TYPE {
		CLASSIC, TIME_ATK, HIGH_SCORES, CREDITS
	};
}

class Menu {
private:
	FontManager* titleFm;
	FontManager* menuFm;
	std::vector<menuNS::SCENE_TYPE> items;
	Input* input;
	int selectedItemIndex;

	float blinkTimer;
	bool blink;

public:
	Menu();
	~Menu();

	void initialize(Input *i, FontManager* fm);
	void update(float frameTime);
	void render();
};

#endif