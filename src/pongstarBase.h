#ifndef _PONGSTARBASE_H
#define _PONGSTARBASE_H
#define _WIN32_LEAN_AND_MEAN

#include <queue>
#include <chrono>

#include "game.h"
#include "dataManager.h"
#include "fontManager.h"
#include "messageManager.h"
#include "pickupManager.h"
#include "entityManager.h"
#include "image.h"
#include "scene.h"

using namespace std::chrono;

namespace pongstarNS {
	const int POINTS_TO_WIN = 5;
	const int TIME_PER_GAME = 10 * 1000;	// milliseconds
	const int TEN_SECONDS = 10 * 1000;
}

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
	std::queue<int> deleteEntityQueue;
	EntityManager* entityManager;

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