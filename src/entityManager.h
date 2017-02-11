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

typedef std::pair<int, float> IntFloatPair;
typedef std::unordered_map<int, float> IntFloatMap;

class EntityManager {
private:
	// Game items
	Game* game;
	TextureManagerMap* tmMap;
	std::map<int, Entity*> entityMap;
	IntFloatMap* pickupDelayTimer;

	int leftPaddleId;
	int rightPaddleId;
	std::vector<int> ballIds;

	bool paddleIdExist;
	
public:
	EntityManager();
	EntityManager(Game* g, TextureManagerMap* tm, IntFloatMap* pdt);
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
	void multiplyBall(int id);
	VECTOR2 getVelocityFromAngle(float angle, float resultantVelocity);

	Paddle* getPaddle(paddleNS::SIDE s);
	std::vector<Paddle*> getPaddles();
	bool hasShield(paddleNS::SIDE s);

	// Entities
	void addEntity(Entity* e);
	Entity* getEntity(int id);
	void deleteEntity(int id);
};

#endif