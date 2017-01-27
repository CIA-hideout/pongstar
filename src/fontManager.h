#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H

#include <map>
#include <string>

#include "font.h"
#include "graphics.h"
#include "textureManager.h"

namespace fontNS {
	const char SABO_FONT_TEXTURE[] = "resources\\font\\sabo.png";
	const char SABO_FONT_INFO[] = "resources\\font\\sabo.dat";
	const char SABO_FILLED_FONT_TEXTURE[] = "resources\\font\\sabo_filled.png";
	const char SABO_FILLED_FONT_INFO[] = "resources\\font\\sabo_filled.dat";
	const int CHAR_WIDTH = 128;
	const int CHAR_HEIGHT = 128;
	const int NCOLS = 16;

	enum FONT_NAME { SABO, SABO_FILLED };
	const int CENTER_OFFSET = 11;
}

typedef std::pair<fontNS::FONT_NAME, Font*> nameFontPair;

class FontManager {
private:
	Graphics* graphics;

	TextureManager saboFontTexture;
	TextureManager saboFilledFontTexure;

	std::map<fontNS::FONT_NAME, Font*> fonts;
	
public:
	FontManager(Graphics* graphics);
	~FontManager();

	void initialize();
	void draw();

	void print(fontNS::FONT_NAME font, int x, int y, std::string text);
	int getTotalWidth(fontNS::FONT_NAME font, std::string text);

	void releaseAll();
	void resetAll();
};

#endif