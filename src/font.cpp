#include <fstream>
#include "font.h"

Font::Font() {

	memset(&this->widths, 0, sizeof(widths));

	spriteData.width = 128;
	spriteData.height = 128;
	spriteData.x = 0;
	spriteData.y = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.scale = 0.5;
	startFrame = 0;
	endFrame = 127;
	currentFrame = 0;
}

Font::~Font() {

}

bool Font::loadTextSprite(TextureManager* texture) {
	return true;
}

bool Font::initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM) {
	return (Image::initialize(g, width, height, ncols, textureM));
}

bool Font::loadTextData(std::string fileName) {
	char buffer[512];

	std::ifstream infile;
	infile.open(fileName.c_str(), std::ios::binary);
	if (!infile) return false;

	// read 512 bytes (2 bytes per character)
	infile.read((char*)(&buffer), 512);
	if (infile.bad()) return false;
	infile.close();

	// convert raw data to proportional data width
	for (int i = 0; i < sizeof(this->widths) / sizeof(this->widths[0]); i++) {
		widths[i] = (int)buffer[i * 2];
	}

	return true;
}

void Font::print(int x, int y, std::string text) {
	float fx = (float)x;
	float fy = (float)y;

	for (size_t i = 0; i < text.length(); i++) {
		int frame = (int)text[i] - '!' + 1;
		if (isdigit(text[i]))
			frame += 32;

		setCurrentFrame(frame);
		setX(fx);
		setY(fy);
		draw();		// repeatedly draw each letter 
		if (widths[frame] == 0)
			widths[frame] = getWidth();

		fx += widths[frame] * getScale();
	}
}

int Font::getTotalWidth(std::string text) {
	float fx = 0;

	for (size_t i = 0; i < text.length(); i++) {
		int frame = (int)text[i] - '!' + 1;
		if (isdigit(text[i]))
			frame += 32;

		fx += widths[frame] * getScale();

	}

	return (int)fx;
}

void Font::draw() {
	Image::draw();
}

void Font::update(float deltaTime) {

}