#include "bumper.h"

// RNG


Bumper::Bumper() : Entity() {
	entityType = entityNS::BUMPER;
	spriteData.width = bumperNS::WIDTH;
	spriteData.height = bumperNS::HEIGHT;
	edge.top = -(long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.bottom = (long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.left = -(long)(bumperNS::WIDTH  * spriteData.scale / 2);
	edge.right = (long)(bumperNS::WIDTH  * spriteData.scale / 2);
	spriteData.scale = 0.5f;

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomBool(0, 1);
	randomBumperX = std::uniform_int_distribution<int>(0, GAME_WIDTH / 4 - spriteData.width * spriteData.scale);
	randomBumperY = std::uniform_int_distribution<int>(0, GAME_HEIGHT - spriteData.height * spriteData.scale);

	float xCoord = randomBool(rng) == 0 ? randomBumperX(rng) + GAME_WIDTH / 2 : randomBumperX(rng) + GAME_WIDTH / 4;

	setX(xCoord);
	setY(randomBumperY(rng));
}

Bumper::~Bumper() {}

bool Bumper::collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager) {
	if (Entity::collidesWith(ent, collisionVector, effectManager)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL:
			randomLocationBumper();
			break;
		}
	}

	return true;
}

void Bumper::randomLocationBumper() {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

	float xCoord;

	if (getX() < GAME_WIDTH / 2)
		xCoord = randomBumperX(rng) + GAME_WIDTH / 2;
	else
		xCoord = randomBumperX(rng) + GAME_WIDTH / 4;

	setX(xCoord);
	setY(randomBumperY(rng));
}