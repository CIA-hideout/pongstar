#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H

#include <vector>
#include <unordered_map>
#include <string>

#include "font.h"
#include "graphics.h"
#include "textureManager.h"

namespace fontNS {
	const int CHAR_WIDTH = 128;
	const int CHAR_HEIGHT = 128;
	const int NCOLS = 16;

	enum FONT_NAME { SABO, SABO_FILLED };
	enum FONT_COLOR { WHITE, BLUE, ORANGE };
	const int CENTER_OFFSET = 11;

	const std::unordered_map<fontNS::FONT_NAME, std::vector<fontNS::FONT_COLOR>> initMap = {
		{ fontNS::SABO, { fontNS::WHITE } },
		{ fontNS::SABO_FILLED, { fontNS::WHITE, fontNS::BLUE, fontNS::ORANGE } }
	};
}

/*
	fonts is a map of names to a map of colors and its specific font pointers.
	The nested map looks like
	std::map<fontNS::FONT_NAME, std::map<fontNS::FONT_COLOR, Font*>>
*/

// color to font pointer
typedef std::pair<fontNS::FONT_COLOR, Font*> colorFontPair;
typedef std::unordered_map<fontNS::FONT_COLOR, Font*> colorFontMap;

// name to colorFontMap pointer
typedef std::pair<fontNS::FONT_NAME, colorFontMap*> nameColorsPair;
typedef std::unordered_map<fontNS::FONT_NAME, colorFontMap*> nameColorsMap;

class FontManager {
private:
	Graphics* graphics;
	std::vector<TextureManager*> textureManagers;
	nameColorsMap fonts;
	
public:
	FontManager(Graphics* graphics);
	~FontManager();

	void initialize();

	void print(fontNS::FONT_NAME n, fontNS::FONT_COLOR c, int x, int y, std::string t);
	int getTotalWidth(fontNS::FONT_NAME n, fontNS::FONT_COLOR c, std::string t);

	void releaseAll();
	void resetAll();
};

#endif