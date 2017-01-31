#include "menu.h"

const char* sceneToString(menuNS::SCENE s) {
	switch (s) {
	case menuNS::CLASSIC:			return "CLASSIC";
	case menuNS::TIME_ATK:			return "TIME ATTACK";
	case menuNS::HIGH_SCORES:		return "HIGH SCORES";
	case menuNS::CREDITS:			return "CREDITS";
	}
}

Menu::Menu() {}

Menu::~Menu() {}

void Menu::initialize(FontManager* fm) {
	// Copy from initialized fm
	titleFm = new FontManager(*fm);
	menuFm = new FontManager(*fm);

	items.push_back(menuNS::CLASSIC);
	items.push_back(menuNS::TIME_ATK);
	items.push_back(menuNS::HIGH_SCORES);
	items.push_back(menuNS::CREDITS);
}

void Menu::update(float frameTime) {

}

void Menu::render() {
	int count = 0;

	titleFm->setScale(fontNS::SABO_FILLED, 1.0);
	titleFm->setScale(fontNS::SABO, 1.0);

	titleFm->setKerning(fontNS::SABO_FILLED, -10);
	titleFm->setKerning(fontNS::SABO, -10);

	int pongstarWidth = titleFm->getTotalWidth(fontNS::SABO_FILLED, "pong") + titleFm->getTotalWidth(fontNS::SABO, "star");
	int pongX = GAME_WIDTH / 2 - pongstarWidth / 2 - fontNS::CENTER_OFFSET;

	titleFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		pongX,
		menuNS::TITLE_Y_POS,
		"pong"
	);

	titleFm->print(
		fontNS::SABO,
		fontNS::WHITE,
		pongX + titleFm->getTotalWidth(fontNS::SABO_FILLED, "pong"),
		menuNS::TITLE_Y_POS,
		"star"
	);

	menuFm->setKerning(fontNS::SABO_FILLED, -4);

	for (std::list<menuNS::SCENE>::iterator it = items.begin(); it != items.end(); ++it) {
		menuFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE,
			GAME_WIDTH / 2 - menuFm->getTotalWidth(fontNS::SABO_FILLED, sceneToString(*it)) / 2,
			menuNS::MENU_Y_POS + count * menuNS::HEIGHT_BETWEEN_ITEM,
			sceneToString(*it)	
		);

		count++;
	}
}