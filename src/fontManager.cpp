#include "fontManager.h"

const char* nameToString(fontNS::FONT_NAME n)
{
	switch (n)
	{
		case fontNS::SABO:			return "sabo";
		case fontNS::SABO_FILLED:   return "sabo_filled";
		default:					return "Unknown font";
	}
}

const char* colorToString(fontNS::FONT_COLOR c)
{
	switch (c)
	{
		case fontNS::WHITE:			return "white";
		case fontNS::BLUE:			return "blue";
		case fontNS::ORANGE:		return "orange";
		default:					return "Unknown color";
	}
}

FontManager::FontManager(Graphics *g) {
	graphics = g;
}

FontManager::~FontManager() {}

void FontManager::initialize() {

	std::vector<fontNS::FONT_COLOR> saboColors = { fontNS::WHITE };
	std::vector<fontNS::FONT_COLOR> saboFilledColors = { fontNS::WHITE, fontNS::BLUE, fontNS::ORANGE };

	std::unordered_map<fontNS::FONT_NAME, std::vector<fontNS::FONT_COLOR>> initMap({
		{ fontNS::SABO, saboColors },
		{ fontNS::SABO_FILLED, saboFilledColors }
	});

	fontNS::FONT_NAME name;
	std::vector<fontNS::FONT_COLOR> colors;
	Font* font;
	TextureManager* tm;
	colorFontMap* tempCFM;

	char fileDirectory[] = "resources\\font\\";

	for (auto& x : initMap) {
		char infoLocation[1024], fontLocation[1024], errorMsg[1024];
		tempCFM = new colorFontMap();

		name = x.first;
		colors = x.second;
		
		sprintf(infoLocation, "%s%s.dat", fileDirectory, nameToString(name));
		printf("%s", infoLocation);

		for (size_t i = 0; i < colors.size(); i++) {
			font = new Font();
			tm = new TextureManager();
			
			sprintf(fontLocation, "%s%s_%s.png", fileDirectory, nameToString(name), colorToString(colors[i]));
			sprintf(errorMsg, "Error initializing %s_%s texture", nameToString(name), colorToString(colors[i]));

			if (!(*tm).initialize(graphics, fontLocation))
				throw(GameError(gameErrorNS::FATAL_ERROR, errorMsg));
			
			font->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, tm);
			font->loadTextData(infoLocation);
			tempCFM->insert(colorFontPair(colors[i], font));

			textureManagers.push_back(tm);
		}

		fonts.insert(nameColorPair(name, tempCFM));
	}




	//if (!saboFontWhiteTexture.initialize(graphics, fontNS::SABO_WHITE_TEXTURE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo font white texture"));

	//if (!saboFilledFontWhiteTexture.initialize(graphics, fontNS::SABO_FILLED_WHITE_TEXTURE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sabo filled font white texture"));

	//Font* saboFontWhite = new Font();
	//saboFontWhite->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFontWhiteTexture);
	//saboFontWhite->loadTextData(fontNS::SABO_INFO);

	//Font* saboFilledFontWhite = new Font();
	//saboFilledFontWhite->initialize(graphics, fontNS::CHAR_WIDTH, fontNS::CHAR_HEIGHT, fontNS::NCOLS, &saboFilledFontWhiteTexture);
	//saboFilledFontWhite->loadTextData(fontNS::SABO_FILLED_INFO);

	//colorFontMap* saboColorMap = new colorFontMap();
	//saboColorMap->insert(colorFontPair(fontNS::WHITE, saboFontWhite));

	//colorFontMap* saboFilledColorMap = new colorFontMap();
	//saboFilledColorMap->insert(colorFontPair(fontNS::WHITE, saboFilledFontWhite));
	//
	//fonts.insert(nameColorPair(fontNS::SABO, saboColorMap));
	//fonts.insert(nameColorPair(fontNS::SABO_FILLED, saboFilledColorMap));

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
	for (size_t i = 0; i < textureManagers.size(); i++) {
		textureManagers[i]->onResetDevice();
	}
}

void FontManager::resetAll() {
	for (size_t i = 0; i < textureManagers.size(); i++) {
		textureManagers[i]->onLostDevice();
	}
}