#ifndef _PONGSTAR_H
#define _PONGSTAR_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <unordered_map>

#include "game.h"
#include "dataManager.h"
#include "fontManager.h"
#include "textureManager.h"
#include "messageManager.h"
#include "image.h"

#include "paddle.h"
#include "ball.h"
#include "bumper.h"

#include "scene.h"
#include "menu.h"
#include "pongstarBase.h"

using namespace std::chrono;

enum GAME_STATE {
	MENU, GAME
};

class Pongstar : public Game {
private:
	// Game items
	DataManager* dataManager;
	FontManager* fontManager;
	TextureManagerMap tmMap;

	Image border;
	Image divider;

	std::vector<Entity*> entityVector;
	std::queue<int> deleteEntityQueue;

	steady_clock::time_point startTime;
	int elapsedTime;
	bool gameStarted;

	Menu* menu;

	GAME_STATE gameState;
	std::stack<Scene> gameStack;
	PongstarBase* ps;

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
