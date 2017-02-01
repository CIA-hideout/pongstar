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

void Menu::initialize(Input* i, FontManager* fm) {
	selectedItemIndex = 0;
	blink = true;
	input = i;

	// Copy from initialized fm
	titleFm = new FontManager(*fm);
	menuFm = new FontManager(*fm);

	items.push_back(menuNS::CLASSIC);
	items.push_back(menuNS::TIME_ATK);
	items.push_back(menuNS::HIGH_SCORES);
	items.push_back(menuNS::CREDITS);
}

void Menu::update(float frameTime) {
	if (input->wasKeyPressed(UP_KEY)) {
		selectedItemIndex = selectedItemIndex == 0 ? items.size() - 1 : selectedItemIndex - 1;
	}

	if (input->wasKeyPressed(DOWN_KEY)) {
		selectedItemIndex = selectedItemIndex == items.size() - 1 ? 0 : selectedItemIndex + 1;
	}

	if (blinkTimer < menuNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}

	if (blinkTimer >= menuNS::BLINK_INTERVAL) {
		blink = !blink;
		blinkTimer = 0.0;
	}
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

	for (size_t i = 0; i < items.size(); i++) {
		int itemWidth = menuFm->getTotalWidth(fontNS::SABO_FILLED, sceneToString(items[i]));
		int itemStartXPos = GAME_WIDTH / 2 - itemWidth / 2;
		int itemStartYPos = menuNS::MENU_Y_POS + i * menuNS::HEIGHT_BETWEEN_ITEM;

		if (selectedItemIndex == i && blink) {
			menuFm->print(
				fontNS::SABO,
				fontNS::WHITE,
				itemStartXPos - menuFm->getTotalWidth(fontNS::SABO, "-") - menuNS::DIST_BTWN_MINUS_AND_ITEM,
				itemStartYPos,
				"-"
			);

			menuFm->print(
				fontNS::SABO,
				fontNS::WHITE,
				itemStartXPos + itemWidth + menuNS::DIST_BTWN_MINUS_AND_ITEM,
				itemStartYPos,
				"-"
			);
		}

		menuFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE,
			itemStartXPos,
			itemStartYPos,
			sceneToString(items[i])
		);
	}
}