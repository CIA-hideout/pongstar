#ifndef _PONGSTAR_H
#define _PONGSTAR_H
#define _WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

class Pongstar : public Game {
private:
	// Game items

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
