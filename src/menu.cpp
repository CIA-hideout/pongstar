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

Menu::Menu(Audio* a, Input* i, FontManager* fm) {
	sceneType = sceneNS::MENU;

	audio = a;
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
}

void Menu::update(float frameTime) {
	if (input->wasKeyPressed(UP_KEY)) {
		selectedItemIndex = selectedItemIndex == 0 ? items.size() - 1 : selectedItemIndex - 1;
		audio->playCue(NAVIGATION_CUE);
	}

	if (input->wasKeyPressed(DOWN_KEY)) {
		selectedItemIndex = selectedItemIndex == items.size() - 1 ? 0 : selectedItemIndex + 1;
		audio->playCue(NAVIGATION_CUE);
	}

	if (input->wasKeyPressed(ENTER_KEY)) {
		if (items[selectedItemIndex] == sceneNS::CLASSIC) {
			sceneData.gameMode = sceneNS::GM_CLASSIC;
			nextSceneType = sceneNS::INSTRUCTIONS;
			audio->playCue(ENTER_CUE);
		}
		else if (items[selectedItemIndex] == sceneNS::TIME_ATK) {
			sceneData.gameMode = sceneNS::GM_TIME_ATK;
			nextSceneType = sceneNS::INSTRUCTIONS;
			audio->playCue(ENTER_CUE);
		}
		else {
			nextSceneType = items[selectedItemIndex];
			audio->playCue(ENTER_CUE);
		}
	}

	if (blinkTimer < menuNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}
	else {
		blink = !blink;
		blinkTimer = 0.0;
	}
}

void Menu::render() {
	float scale = menuNS::TITLE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	titleFm->setScale(fontNS::SABO_FILLED, scale);
	titleFm->setScale(fontNS::SABO, scale);
	titleFm->setKerning(fontNS::SABO_FILLED, 50);
	titleFm->setKerning(fontNS::SABO, 50);

	int titleWidth = titleFm->getTotalWidth(fontNS::SABO_FILLED, "pong") + titleFm->getTotalWidth(fontNS::SABO, "star");
	int titleXpos = GAME_WIDTH / 2 - titleWidth / 2 - fontNS::CENTER_OFFSET;

	titleFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		titleXpos,
		menuNS::TITLE_Y_POS,
		"pong"
	);

	titleFm->print(
		fontNS::SABO,
		fontNS::WHITE,
		titleXpos + titleFm->getTotalWidth(fontNS::SABO_FILLED, "pong"),
		menuNS::TITLE_Y_POS,
		"star"
	);

	scale = menuNS::MENU_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	menuFm->setScale(fontNS::SABO_FILLED, scale);
	menuFm->setScale(fontNS::SABO, scale);
	menuFm->setKerning(fontNS::SABO_FILLED, 3);

	for (size_t i = 0; i < items.size(); i++) {
		int itemWidth = menuFm->getTotalWidth(fontNS::SABO_FILLED, sceneToString(items[i]));
		int itemXpos = GAME_WIDTH / 2 - itemWidth / 2 - fontNS::CENTER_OFFSET;
		int itemYpos = menuNS::MENU_Y_POS + (menuFm->getHeight(fontNS::SABO_FILLED) + menuNS::MENU_VERT_GAP) * i;

		if (selectedItemIndex == i && blink) {
			menuFm->print(
				fontNS::SABO,
				fontNS::ORANGE,
				itemXpos - menuFm->getTotalWidth(fontNS::SABO, "-") - menuNS::BLINKER_GAP,
				itemYpos,
				"-"
			);

			menuFm->print(
				fontNS::SABO,
				fontNS::BLUE,
				itemXpos + itemWidth + menuNS::BLINKER_GAP,
				itemYpos,
				"-"
			);
		}

		menuFm->print(
			fontNS::SABO_FILLED,
			fontNS::WHITE,
			itemXpos,
			itemYpos,
			sceneToString(items[i])
		);
	}
}