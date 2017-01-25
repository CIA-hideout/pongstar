#ifndef _PONGSTAR_H
#define _PONGSTAR_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <random>
#include <queue>
#include <chrono>

#include "game.h"
#include "dataManager.h"
#include "fontManager.h"
#include "pickupManager.h"
#include "textureManager.h"
#include "messageManager.h"
#include "image.h"

#include "paddle.h"
#include "ball.h"
#include "bumper.h"

using namespace std::chrono;

class Pongstar : public Game {
private:
	// Game items
	DataManager* dataManager;
	FontManager* fontManager;
	PickupManager* pickupManager;
	MessageManager* messageManager;

	TextureManager dividerTexture;
	TextureManager paddleTexture;
	TextureManager ballTexture;
	TextureManager bumperTexture;

	Image divider;

	std::vector<Entity*> entityVector;
	std::queue<int> deleteEntityQueue;

	steady_clock::time_point startTime;
	int elapsedTime;
	bool gameStarted;

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
