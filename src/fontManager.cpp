#include "fontManager.h"

FontManager::FontManager(Graphics *g) {
	graphics = g;
}

FontManager::~FontManager() {}

void FontManager::initialize() {
	if (!saboFontWhiteTexture.initialize(graphics, fontNS::SABO_WHITE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo font white texture"));

	if (!saboFilledFontWhiteTexture.initialize(graphics, fontNS::SABO_FILLED_WHITE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo filled font white texture"));

	Font* saboFontWhite = new Font();
	saboFontWhite->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFontWhiteTexture);
	saboFontWhite->loadTextData(fontNS::SABO_INFO);

	Font* saboFilledFontWhite = new Font();
	saboFilledFontWhite->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFilledFontWhiteTexture);
	saboFilledFontWhite->loadTextData(fontNS::SABO_FILLED_INFO);

	colorFontMap* saboColorMap = new colorFontMap();
	saboColorMap->insert(colorFontPair(fontNS::WHITE, saboFontWhite));

	colorFontMap* saboFilledColorMap = new colorFontMap();
	saboFilledColorMap->insert(colorFontPair(fontNS::WHITE, saboFilledFontWhite));
	
	fonts.insert(nameColorPair(fontNS::SABO, saboColorMap));
	fonts.insert(nameColorPair(fontNS::SABO_FILLED, saboFilledColorMap));

	//fonts.insert(nameFontPair(fontNS::SABO, saboFont));
	//fonts.insert(nameFontPair(fontNS::SABO_FILLED, saboFilledFont));
}

void FontManager::draw() {
	//for (const nameFontPair& i : fonts) {	// access by reference
	//	// i.first - key
	//	// i.second - data
	//	i.second->draw();
	//}
}

void FontManager::print(fontNS::FONT_NAME name, fontNS::FONT_COLOR color, int x, int y, std::string text) {
	(*fonts[name])[color]->print(x, y, text);
}

int FontManager::getTotalWidth(fontNS::FONT_NAME name, fontNS::FONT_COLOR color, std::string text) {
	return (*fonts[name])[color]->getTotalWidth(text);
}

void FontManager::releaseAll() {
	saboFontWhiteTexture.onLostDevice();
	saboFilledFontWhiteTexture.onLostDevice();
}

void FontManager::resetAll() {
	saboFontWhiteTexture.onLostDevice();
	saboFilledFontWhiteTexture.onLostDevice();
}