#ifndef _PONGSTAR_H
#define _PONGSTAR_H
#define _WIN32_LEAN_AND_MEAN

#include <stack>

#include "game.h"
#include "dataManager.h"
#include "fontManager.h"

#include "scene.h"
#include "menu.h"
#include "classic.h"
#include "timeAttack.h"

class Pongstar : public Game {
private:
	// Game items
	DataManager* dataManager;
	FontManager* fontManager;
	TextureManagerMap tmMap;

	std::stack<Scene*>* gameStack;

public:
	// Constructor
	Pongstar();

	// Destructor
	virtual ~Pongstar();

	// Initialize the game
	void initialize(HWND hwnd);

	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
