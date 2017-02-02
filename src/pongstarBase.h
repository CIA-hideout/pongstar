#ifndef _PONGSTARBASE_H
#define _PONGSTARBASE_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <stack>
#include <chrono>

#include "game.h"
#include "gameError.h"
#include "dataManager.h"
#include "fontManager.h"
#include "textureManager.h"
#include "messageManager.h"
#include "pickupManager.h"
#include "image.h"

#include "paddle.h"
#include "ball.h"
#include "bumper.h"
#include "scene.h"

using namespace std::chrono;

namespace pongstarNS {
	enum TEXTURE { BALL, PADDLE, DIVIDER, BUMPER, PICKUPS };
	const char TEXTURE_DIRECTORY[] = "sprites\\";

	const std::vector<TEXTURE> initTextureVec = {
		TEXTURE::BALL,
		TEXTURE::PADDLE,
		TEXTURE::DIVIDER,
		TEXTURE::BUMPER,
		TEXTURE::PICKUPS
	};
}

typedef std::unordered_map<pongstarNS::TEXTURE, TextureManager*> TextureManagerMap;

class PongstarBase : public Scene {
private:
	// Game items
	Game* game;
	Input* input;
	FontManager* fontManager;
	DataManager* dataManager;
	TextureManagerMap tmMap;

	MessageManager* messageManager;
	PickupManager* pickupManager;
	Image divider;

	std::vector<Entity*> entityVector;
	std::queue<int> deleteEntityQueue;

	steady_clock::time_point startTime;
	int elapsedTime;
	bool gameStarted;

public:
	PongstarBase(Game* g, Input* i, DataManager* dm, FontManager* fm, TextureManagerMap t);
	~PongstarBase();

	virtual void initialize(Image d);
	void initializeEntities();

	// Interface
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void render();

	virtual void releaseAll();
	virtual void resetAll();
};

#endif