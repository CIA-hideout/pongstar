#include "fontManager.h"

const char* nameToString(fontNS::FONT_NAME n) {
	switch (n) {
		case fontNS::SABO:			return "sabo";
		case fontNS::SABO_FILLED:   return "sabo_filled";
	}
}

const char* colorToString(fontNS::FONT_COLOR c) {
	switch (c) {
		case fontNS::WHITE:			return "white";
		case fontNS::BLUE:			return "blue";
		case fontNS::ORANGE:		return "orange";
	}
}

FontManager::FontManager(Graphics *g) {
	graphics = g;
}

FontManager::~FontManager() {}

void FontManager::initialize() {
	fontNS::FONT_NAME name;
	std::vector<fontNS::FONT_COLOR> colorsVec;
	Font* font;
	TextureManager* tm;
	colorFontMap* cfm;

	char fileDirectory[] = "resources\\font\\";

	for (auto& x : fontNS::initMap) {
		char infoLocation[1024], fontLocation[1024], errorMsg[1024];
		cfm = new colorFontMap();

		name = x.first;
		colorsVec = x.second;
		
		sprintf(infoLocation, "%s%s.dat", fileDirectory, nameToString(name));

		for (size_t i = 0; i < colorsVec.size(); i++) {
			font = new Font();
			tm = new TextureManager();
			
			sprintf(fontLocation, "%s%s_%s.png", fileDirectory, nameToString(name), colorToString(colorsVec[i]));
			sprintf(errorMsg, "Error initializing %s_%s texture", nameToString(name), colorToString(colorsVec[i]));

			if (!(*tm).initialize(graphics, fontLocation))
				throw(GameError(gameErrorNS::FATAL_ERROR, errorMsg));
			
			font->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, tm);
			font->loadTextData(infoLocation);
			cfm->insert(colorFontPair(colorsVec[i], font));

			textureManagers.push_back(tm);
		}

		fonts.insert(nameColorsPair(name, cfm));
	}
}

void FontManager::print(fontNS::FONT_NAME name, fontNS::FONT_COLOR color, int x, int y, std::string text) {
	(*fonts[name])[color]->print(x, y, text);
}

int FontManager::getTotalWidth(fontNS::FONT_NAME name, fontNS::FONT_COLOR color, std::string text) {
	return (*fonts[name])[color]->getTotalWidth(text);
}

void FontManager::releaseAll() {
	for (size_t i = 0; i < textureManagers.size(); i++) {
		textureManagers[i]->onResetDevice();
	}
}

void FontManager::resetAll() {
	for (size_t i = 0; i < textureManagers.size(); i++) {
		textureManagers[i]->onLostDevice();
	}
}