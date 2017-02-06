#include "ballManager.h"

BallManager::BallManager() {}

BallManager::BallManager(Game* g, TextureManager* bt, std::vector<Entity*>* ev) {
	game = g;
	ballTexture = bt;
	entityVector = ev;
	ballCount = 0;
}

BallManager::~BallManager() {}

Ball* BallManager::createBall() {
	Ball* ball = new Ball();

	if (!ball->initialize(game, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, ballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	entityVector->push_back(ball);
	ballCount++;
	return ball;
}

VECTOR2 BallManager::getVelocityFromAngle(float angle) {
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