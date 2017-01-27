#include "bumper.h"

Bumper::Bumper() : Entity() {
	entityType = entityNS::BUMPER;
	spriteData.width = bumperNS::WIDTH;
	spriteData.height = bumperNS::HEIGHT;
	edge.top = -(long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.bottom = (long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.left = -(long)(bumperNS::WIDTH  * spriteData.scale / 2);
	edge.right = (long)(bumperNS::WIDTH  * spriteData.scale / 2);

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomBool(0, 1);
	randomBumperX = std::uniform_int_distribution<int>(0, GAME_WIDTH / 4 - (int)(spriteData.width * spriteData.scale));
	randomBumperY = std::uniform_int_distribution<int>(TOP_WALL, BOTTOM_WALL - (int)(spriteData.height * spriteData.scale));

	int xCoord = randomBumperX(rng);

	if (randomBool(rng) == 0) {
		// Spawn bumper on right side;
		xCoord += GAME_WIDTH / 2;
		side = bumperNS::RIGHT;
	}
	else {
		// Spawn bumper on left side
		xCoord += GAME_WIDTH / 4;
		side = bumperNS::LEFT;
	}

	setX((float)xCoord);
	setY((float)randomBumperY(rng));
}

Bumper::~Bumper() {}

bool Bumper::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	Message* msgPtr = NULL;

	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL:
			// Set message to spawn pickup
			messageNS::PICKUP_CMD direction = (side == bumperNS::LEFT) ? messageNS::MOVE_RIGHT : messageNS::MOVE_LEFT;
			msgPtr = new Message(messageNS::PICKUP, direction);
			setMessage(msgPtr);

			// Move bumper
			randomLocationBumper();
			break;
		}
	}

	return true;
}

void Bumper::randomLocationBumper() {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

	int xCoord = randomBumperX(rng);

	if (side == bumperNS::LEFT) {
		// Spawn bumper on right side;
		xCoord += GAME_WIDTH / 2;
		side = bumperNS::RIGHT;
	}
	else {
		// Spawn bumper on left side
		xCoord += GAME_WIDTH / 4;
		side = bumperNS::LEFT;
	}

	setX((float)xCoord);
	setY((float)randomBumperY(rng));
}