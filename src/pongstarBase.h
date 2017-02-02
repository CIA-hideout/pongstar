#ifndef _PONGSTARBASE_H
#define _PONGSTARBASE_H
#define _WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <stack>
#include <chrono>

#include "gameError.h"
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

using namespace std::chrono;


namespace pongstarNS {
	enum TEXTURE { BALL, PADDLE, DIVIDER, BUMPER };
	const char TEXTURE_DIRECTORY[] = "sprites\\";

	const std::vector<TEXTURE> initTextureVec = {
		TEXTURE::BALL,
		TEXTURE::PADDLE,
		TEXTURE::DIVIDER,
		TEXTURE::BUMPER
	};
}

typedef std::unordered_map<pongstarNS::TEXTURE, TextureManager*> TextureManagerMap;

class PongstarBase : public Scene {
private:
	// Game items
	MessageManager* messageManager;
	FontManager* fontManager;
	DataManager* dataManager;
	TextureManagerMap tmMap;
	Game* game;
	Input* input;

	Image divider;

	std::vector<Entity*> entityVector;
	std::queue<int> deleteEntityQueue;

	steady_clock::time_point startTime;
	int elapsedTime;
	bool gameStarted;

public:
	PongstarBase(DataManager* dm, FontManager* fm, MessageManager* mm, TextureManagerMap t, Game* g, Input* i);
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