#ifndef _MENU_H
#define _MENU_H

#include "graphics.h"
#include "fontManager.h"
#include <list>

namespace menuNS {
	const int TITLE_Y_POS = 70;
	const int MENU_Y_POS = 250;
	const int HEIGHT_BETWEEN_ITEM = 90;
	enum SCENE {
		CLASSIC, TIME_ATK, HIGH_SCORES, CREDITS
	};
}

class Menu {
private:
	FontManager* titleFm;
	FontManager* menuFm;
	std::list<menuNS::SCENE> items;

public:
	Menu();
	~Menu();

	void initialize(FontManager* fm);
	void update(float frameTime);
	void render();
};

#endif