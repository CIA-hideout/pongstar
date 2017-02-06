#include "menu.h"

const char* sceneToString(sceneNS::TYPE s) {
	switch (s) {
	case sceneNS::CLASSIC:			return "CLASSIC";
	case sceneNS::TIME_ATK:			return "TIME ATTACK";
	case sceneNS::HIGH_SCORES:		return "HIGH SCORES";
	case sceneNS::CREDITS:			return "CREDITS";
	default:						return "Invalid scene type found";
	}
}

Menu::Menu() {};

Menu::Menu(Input* i, FontManager* fm) {
	sceneType = sceneNS::MENU;

	input = i;
	baseFm = fm;
}

Menu::~Menu() {}

void Menu::initialize(sceneNS::SceneData sd) {
	selectedItemIndex = 0;
	blink = true;

	// Copy from initialized fm
	titleFm = new FontManager(*baseFm);
	menuFm = new FontManager(*baseFm);

	items.push_back(sceneNS::CLASSIC);
	items.push_back(sceneNS::TIME_ATK);
	items.push_back(sceneNS::HIGH_SCORES);
	items.push_back(sceneNS::CREDITS);

	sceneData.hsDisplayMode = sceneNS::HS_BOTH;
}

void Menu::update(float frameTime) {
	if (input->wasKeyPressed(UP_KEY)) {
		selectedItemIndex = selectedItemIndex == 0 ? items.size() - 1 : selectedItemIndex - 1;
	}

	if (input->wasKeyPressed(DOWN_KEY)) {
		selectedItemIndex = selectedItemIndex == items.size() - 1 ? 0 : selectedItemIndex + 1;
	}

	if (input->wasKeyPressed(ENTER_KEY)) {
		nextSceneType = items[selectedItemIndex];
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
	titleFm->setScale(fontNS::SABO_FILLED, 0.625);
	titleFm->setScale(fontNS::SABO, 0.625);

	titleFm->setKerning(fontNS::SABO_FILLED, 50);
	titleFm->setKerning(fontNS::SABO, 50);

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

	menuFm->setScale(fontNS::SABO_FILLED, 0.3125);
	menuFm->setScale(fontNS::SABO, 0.3125);
	menuFm->setKerning(fontNS::SABO_FILLED, 3);

	for (size_t i = 0; i < items.size(); i++) {
		int itemWidth = menuFm->getTotalWidth(fontNS::SABO_FILLED, sceneToString(items[i]));
		int itemStartXPos = GAME_WIDTH / 2 - itemWidth / 2;
		int itemStartYPos = menuNS::MENU_Y_POS + (menuFm->getHeight(fontNS::SABO_FILLED) + menuNS::HEIGHT_BETWEEN_ITEM) * i;

		if (selectedItemIndex == i && blink) {
			menuFm->print(
				fontNS::SABO,
				fontNS::ORANGE,
				itemStartXPos - menuFm->getTotalWidth(fontNS::SABO, "-") - menuNS::DIST_BTWN_MINUS_AND_ITEM,
				itemStartYPos,
				"-"
			);

			menuFm->print(
				fontNS::SABO,
				fontNS::BLUE,
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