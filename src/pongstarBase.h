#ifndef _PONGSTARBASE_H
#define _PONGSTARBASE_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <chrono>

#include "game.h"
#include "dataManager.h"
#include "fontManager.h"
#include "textureManager.h"
#include "messageManager.h"
#include "pickupManager.h"
#include "ballManager.h"
#include "image.h"

#include "bumper.h"

#include "scene.h"

using namespace std::chrono;

namespace pongstarNS {
	enum TEXTURE { BALL, PADDLE, DIVIDER, BUMPER, BORDER, PICKUPS };
	const char TEXTURE_DIRECTORY[] = "sprites\\";

	const std::vector<TEXTURE> initTextureVec = {
		BALL,
		PADDLE,
		DIVIDER,
		BUMPER,
		BORDER,
		PICKUPS
	};

	const int POINTS_TO_WIN = 5;
	const int TIME_PER_GAME = 10 * 1000;	// milliseconds
	const int TEN_SECONDS = 10 * 1000;
}

typedef std::unordered_map<pongstarNS::TEXTURE, TextureManager*> TextureManagerMap;

class PongstarBase : public Scene {
protected:
	// Game items
	Game* game;
	FontManager* fontManager;
	DataManager* dataManager;
	TextureManagerMap tmMap;

	// Scene items
	MessageManager* messageManager;
	PickupManager* pickupManager;
	BallManager* ballManager;
	std::vector<Entity*> entityVector;
	std::queue<int> deleteEntityQueue;

	// Other sprites that are not entities
	Image divider;
	Image border;

	steady_clock::time_point startTime;
	int elapsedTime;
	bool gameStarted;

public:
	PongstarBase(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t);
	~PongstarBase();

	void initializeEntities();

	// Interface
	virtual void initialize(sceneNS::SceneData sd);	// initialize base pongstar items
	virtual void update(float frameTime);
	virtual void ai();
	virtual void collisions();
	virtual void render();

	virtual void releaseAll();
	virtual void resetAll();
};

#endif