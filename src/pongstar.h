#ifndef _PONGSTAR_H
#define _PONGSTAR_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <random>

#include "game.h"
#include "textureManager.h"
#include "dataManager.h"
#include "image.h"

#include "paddle.h"
#include "ball.h"

class Pongstar : public Game {
private:
	// Game items
	DataManager *dataManager;

	TextureManager dividerTexture;
	TextureManager paddleTexture;
	TextureManager ballTexture;

	Image divider;

	std::vector<Entity*> entityVector;

public:
	// Constructor
	Pongstar();

	// Destructor
	virtual ~Pongstar();

	// Initialize the game
	void initialize(HWND hwnd);
	void initializeEntities();

	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
