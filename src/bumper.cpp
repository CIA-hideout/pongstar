#include "bumper.h"

Bumper::Bumper() : Entity() {
	entityType = entityNS::BUMPER;
	spriteData.width = bumperNS::WIDTH;
	spriteData.height = bumperNS::HEIGHT;
	edge.top = -(long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.bottom = (long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.left = -(long)(bumperNS::WIDTH  * spriteData.scale / 2);
	edge.right = (long)(bumperNS::WIDTH  * spriteData.scale / 2);
	spriteData.scale = 0.5f;
}

Bumper::~Bumper() {}

bool Bumper::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	// RNG
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomBumperX(0, GAME_WIDTH / 4 - spriteData.width * spriteData.scale);
	std::uniform_int_distribution<int> randomBumperY(0, GAME_HEIGHT - spriteData.height * spriteData.scale);

	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL:
			if (getX() < GAME_WIDTH / 2)
				setX(randomBumperX(rng) + GAME_WIDTH / 2);
			else
				setX(randomBumperX(rng) + GAME_WIDTH / 4);
			setY(randomBumperY(rng));
			break;
		}
	}

	return true;
}