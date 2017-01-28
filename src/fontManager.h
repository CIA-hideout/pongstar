#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H

#include <map>
#include <unordered_map>
#include <string>

#include "font.h"
#include "graphics.h"
#include "textureManager.h"

namespace fontNS {
	const char SABO_INFO[] = "resources\\font\\sabo.dat";
	const char SABO_FILLED_INFO[] = "resources\\font\\sabo_filled.dat";
	
	// Textures
	const char SABO_WHITE_TEXTURE[] = "resources\\font\\sabo_white.png";
	const char SABO_FILLED_WHITE_TEXTURE[] = "resources\\font\\sabo_filled_white.png";
	const char SABO_FILLED_BLUE_TEXTURE[] = "resources\\font\\sabo_filled_blue.png";
	const char SABO_FILLED_ORANGE_TEXTURE[] = "resources\\font\\sabo_filled_orange.png";

	const int CHAR_WIDTH = 128;
	const int CHAR_HEIGHT = 128;
	const int NCOLS = 16;

	enum FONT_NAME { SABO, SABO_FILLED };
	enum FONT_COLOR { WHITE, BLUE, ORANGE };
	const int CENTER_OFFSET = 11;
}

typedef std::pair<fontNS::FONT_COLOR, Font*> colorFontPair;
typedef std::unordered_map<fontNS::FONT_COLOR, Font*> colorFontMap;

typedef std::pair<fontNS::FONT_NAME, colorFontMap*> nameColorPair;
typedef std::unordered_map<fontNS::FONT_NAME, colorFontMap*> nameColorMap;

class FontManager {
private:
	Graphics* graphics;

	TextureManager saboFontWhiteTexture;
	TextureManager saboFilledFontWhiteTexture;

	//std::map<fontNS::FONT_NAME, Font*> fonts;
	nameColorMap fonts;
	
public:
	FontManager(Graphics* graphics);
	~FontManager();

	void initialize();
	void draw();

	void print(fontNS::FONT_NAME n, fontNS::FONT_COLOR c, int x, int y, std::string t);
	int getTotalWidth(fontNS::FONT_NAME n, fontNS::FONT_COLOR c, std::string t);

	void releaseAll();
	void resetAll();
};

#endif