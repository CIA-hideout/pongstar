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
	enum FONT_COLOR { WHITE, BLUE, ORANGE, RED, GREY };
	const int CENTER_OFFSET = 11;
	const int CENTER_OFFSET_MAX_SCALE = 11 / 4 * 10;

	const std::unordered_map<fontNS::FONT_NAME, std::vector<fontNS::FONT_COLOR>> initMap = {
		{ fontNS::SABO, { fontNS::WHITE, fontNS::BLUE, fontNS::ORANGE, fontNS::RED} },
		{ fontNS::SABO_FILLED, { fontNS::WHITE, fontNS::BLUE, fontNS::ORANGE, fontNS::RED, fontNS::BLUE, fontNS::ORANGE, fontNS::RED } }
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
	FontManager();
	FontManager(Graphics* graphics);
	FontManager(const FontManager& fm);	// copy constructor

	~FontManager();

	void initialize();

	void setScale(fontNS::FONT_NAME n, float s);
	void setKerning(fontNS::FONT_NAME n, int k);

	void print(fontNS::FONT_NAME n, fontNS::FONT_COLOR c, int x, int y, std::string t);
	int getTotalWidth(fontNS::FONT_NAME n, std::string t);
	int getHeight(fontNS::FONT_NAME n);

	void releaseAll();
	void resetAll();
};

#endif