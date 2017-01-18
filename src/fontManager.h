#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H

#include <map>
#include <string>

#include "constants.h"
#include "textureManager.h"
#include "font.h"
#include "graphics.h"

namespace fontNS {
	enum FONT_NAME { SABO, SABO_FILLED };
}

typedef std::pair<fontNS::FONT_NAME, Font*> nameFontPair;

class FontManager {
private:
	Graphics* graphics;

	TextureManager saboFontTexture;
	TextureManager saboFilledFontTexure;

	std::map<fontNS::FONT_NAME, Font*> fonts;
	
public:
	FontManager(Graphics *graphics);
	~FontManager();

	void initialize();
	void draw();

	void print(fontNS::FONT_NAME font, int x, int y, std::string text);
	int getTotalWidth(fontNS::FONT_NAME font, std::string text);

	void releaseAll();
	void resetAll();
};

#endif