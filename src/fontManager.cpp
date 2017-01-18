#include "fontManager.h"

FontManager::FontManager(Graphics *g) {
	graphics = g;
}

FontManager::~FontManager() {}

void FontManager::initialize() {
	if (!saboFontTexture.initialize(graphics, fontNS::SABO_FONT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo font texture"));

	if (!saboFilledFontTexure.initialize(graphics, fontNS::SABO_FILLED_FONT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo filled font texture"));

	Font* saboFont = new Font();
	saboFont->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFontTexture);
	saboFont->loadTextData(fontNS::SABO_FONT_INFO);

	Font* saboFilledFont = new Font();
	saboFilledFont->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFilledFontTexure);
	saboFilledFont->loadTextData(fontNS::SABO_FILLED_FONT_INFO);

	fonts.insert(nameFontPair(fontNS::SABO, saboFont));
	fonts.insert(nameFontPair(fontNS::SABO_FILLED, saboFilledFont));
}

void FontManager::draw() {
	for (const nameFontPair& i : fonts) {	// access by reference
		// i.first - key
		// i.second - data
		i.second->draw();
	}
}

void FontManager::print(fontNS::FONT_NAME fontName, int x, int y, std::string text) {
	fonts[fontName]->print(x, y, text);
}

int FontManager::getTotalWidth(fontNS::FONT_NAME fontName, std::string text) {
	return fonts[fontName]->getTotalWidth(text);
}

void FontManager::releaseAll() {
	saboFontTexture.onLostDevice();
	saboFontTexture.onLostDevice();
}

void FontManager::resetAll() {
	saboFontTexture.onLostDevice();
	saboFilledFontTexure.onLostDevice();
}