#include "entityManager.h"

EntityManager::EntityManager() {}

EntityManager::EntityManager(Game* g, TextureManagerMap* t, IntFloatMap* pdt) {
	game = g;
	tmMap = t;
	pickupDelayTimer = pdt;
}

EntityManager::~EntityManager() {}

void EntityManager::initialize() {}

TextureManager* EntityManager::getEntityTexture(entityNS::ENTITY_TYPE et) {
	switch (et) {
		case entityNS::BALL: return (*tmMap)[textureNS::BALL];
		case entityNS::BUMPER: return (*tmMap)[textureNS::BUMPER];
		case entityNS::PICKUP: return (*tmMap)[textureNS::PICKUPS];
		default: return new TextureManager();
	}
}

void EntityManager::addEntity(Entity* entity) {
	pickupDelayTimer->insert(IntFloatPair(entity->getId(), 0.0f));
	entityMap.insert(IdEntityPair(entity->getId(), entity));
}

Entity* EntityManager::getEntity(int id) {
	return entityMap[id];
}

Paddle* EntityManager::getPaddle(paddleNS::SIDE s) {
	if (!paddleIdExist) {
		Paddle* p;

		for (auto& x : entityMap) {
			if (x.second->getEntityType() == entityNS::PADDLE) {
				// store paddle id
				p = (Paddle*)x.second;

				if (p->getSide() == paddleNS::LEFT)
					leftPaddleId = p->getId();
				else
					rightPaddleId = p->getId();
			}
		}
	}

	return s == paddleNS::LEFT ? (Paddle*)entityMap[leftPaddleId] : (Paddle*)entityMap[rightPaddleId];
}

std::vector<Paddle*> EntityManager::getPaddles() {	
	std::vector<Paddle*> pv;
	pv.push_back(getPaddle(paddleNS::LEFT));
	pv.push_back(getPaddle(paddleNS::RIGHT));

	return pv;
}

void EntityManager::deleteEntity(int id) {
	entityMap.erase(id);
}

Ball* EntityManager::createBall() {
	Ball* ball = new Ball();

	if (!ball->initialize(game, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, (*tmMap)[textureNS::BALL]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	addEntity(ball);
	ballIds.push_back(ball->getId());
	return ball;
}

std::vector<Ball*> EntityManager::getBalls() {
	std::vector<Ball*> bv;

	for (size_t i = 0; i < ballIds.size(); i++) {
		bv.push_back((Ball*)entityMap[ballIds[i]]);
	}

	return bv;
}

void EntityManager::deleteBall(int id) {
	if (ballIds.size() > 1) {
		entityMap[id]->setActive(false);
		ballIds.erase(std::remove(ballIds.begin(), ballIds.end(), id), ballIds.end());
	} else {
		getEntity(id)->setVisible(true);
	}
}

void EntityManager::multiplyBall(int id) {
	Ball* currentBall = (Ball*)getEntity(id);
	float ballAngle = currentBall->getBallAngle();
	VECTOR2 newVelocity;

	Ball* newBall1 = createBall();
	newBall1->setX(currentBall->getX());
	newBall1->setY(currentBall->getY());
	newVelocity = getVelocityFromAngle(ballAngle + 30);
	newBall1->setVelocity(newVelocity);

	Ball* newBall2 = createBall();
	newBall2->setX(currentBall->getX());
	newBall2->setY(currentBall->getY());
	newVelocity = getVelocityFromAngle(ballAngle - 30);
	newBall2->setVelocity(newVelocity);
}

VECTOR2 EntityManager::getVelocityFromAngle(float angle) {
	float theta = std::fmod(angle, 90);
	float velocity1 = ((90 - theta) / 90) * ballNS::VELOCITY;
	float velocity2 = (theta / 90) * ballNS::VELOCITY;
	VECTOR2 velocity;

	if (angle >= 0 && angle < 90) {
		velocity = VECTOR2(velocity2, -velocity1);
	}
	else if (angle >= 90 && angle < 180) {
		velocity = VECTOR2(velocity1, velocity2);
	}
	else if (angle >= 180 && angle < 270) {
		velocity = VECTOR2(-velocity2, velocity1);
	}
	else if (angle >= 270 && angle < 360) {
		velocity = VECTOR2(-velocity1, -velocity2);
	}

	return velocity;
}
