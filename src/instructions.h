#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "game.h"
#include "scene.h"
#include "fontManager.h"
#include "textureManager.h"

namespace instructionsNS {
	const int TITLE_Y_POS = 90;
	const float TITLE_FONT_SIZE = 50.0;
	const int TEXT_Y_POS = 600;
	const float TEXT_FONT_SIZE = 30.0;
	const int BLINKER_GAP = 20;
	const float BLINK_INTERVAL = 0.2f;
}

class Instructions : public Scene {
private:
	Audio* audio;
	Game* game;
	FontManager* baseFm;
	sceneNS::GAME_MODE gameMode;

	Image instructions;
	TextureManager instructionsTexture;

	FontManager* titleFm;
	FontManager* textFm;

	float blinkTimer;
	bool blink;

public:
	Instructions();
	Instructions(Audio* a, Game* g, FontManager* fm);
	~Instructions();

	void initialize(sceneNS::SceneData sd);
	void update(float frameTime);
	void ai() {};
	void collisions() {};
	void render();
	void renderTitle(std::string firstWord, std::string secondWord);

	void releaseAll();
	void resetAll();
};

#endif
