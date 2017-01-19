#ifndef _FONT_H_
#define _FONT_H_

#include <string>

#include "image.h"

class Font : public Image {
private:
	int widths[256];
	std::string text;

public:
	Font();
	~Font();

	bool loadTextData(std::string fileName);
	bool loadTextSprite(TextureManager* texture);
	void print(int x, int y, std::string text);
	virtual void draw();
	virtual bool initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM);

	int getTotalWidth(std::string text);
};

#endif