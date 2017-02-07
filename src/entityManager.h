#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <map>
#include <vector>
#include <algorithm>

#include "game.h"
#include "entity.h"
#include "ball.h"
#include "paddle.h"
#include "bumper.h"
#include "textureManager.h"

namespace textureNS {
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
}

typedef std::pair<int, Entity*> IdEntityPair;
typedef std::unordered_map<textureNS::TEXTURE, TextureManager*> TextureManagerMap;

class EntityManager {
private:
	// Game items
	Game* game;
	TextureManagerMap* tmMap;
	std::map<int, Entity*> entityMap;

	int leftPaddleId;
	int rightPaddleId;
	std::vector<int> ballIds;

	bool paddleIdExist;
	
public:
	EntityManager();
	EntityManager(Game* g, TextureManagerMap* t);
	~EntityManager();

	void initialize();
	TextureManager* getEntityTexture(entityNS::ENTITY_TYPE et);
	std::map<int, Entity*>* getEntityMap() { return &entityMap; }
	void setEntityMap(std::map<int, Entity*>* em) { entityMap = *em; }

	// Ball
	Ball* createBall();
	std::vector<Ball*> getBalls();
	int getBallCount() { return ballIds.size(); };
	void deleteBall(int id);	// validate if ball can be deleted
	VECTOR2 getVelocityFromAngle(float angle);

	Paddle* getPaddle(paddleNS::SIDE side);
	std::vector<Paddle*> getPaddles();

	// Entities
	void addEntity(Entity* e);
	Entity* getEntity(int id);
	void deleteEntity(int id);
};

#endif