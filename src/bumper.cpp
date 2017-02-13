#include "bumper.h"

Bumper::Bumper() : Entity() {
	entityType = entityNS::BUMPER;
	spriteData.width = bumperNS::WIDTH;
	spriteData.height = bumperNS::HEIGHT;
	side = randBool() ? bumperNS::LEFT : bumperNS::RIGHT;

	randomLocationBumper();
	calibrateEdges();
}

Bumper::~Bumper() {}

int Bumper::getRandXSpawn() {
	return randInt(0, GAME_WIDTH / 4 - (int)(spriteData.width * spriteData.scale.x));
}

int Bumper::getRandYSpawn() {
	return randInt(TOP_WALL, BOTTOM_WALL - (int)(spriteData.height * spriteData.scale.y));
}

bool Bumper::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	Message* msgPtr;

	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
			case entityNS::BALL: {
				// Set message to spawn pickup
				messageNS::PICKUP_CMD direction = (side == bumperNS::LEFT) ? messageNS::MOVE_RIGHT : messageNS::MOVE_LEFT;
				msgPtr = new Message(messageNS::PICKUP, direction);
				pushMsg(msgPtr);
			} break;

			default: break;
		}
	}

	return true;
}

void Bumper::randomLocationBumper() {
	int xCoord = getRandXSpawn();

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

	spriteData.x = (float)xCoord;
	spriteData.y = (float)getRandYSpawn();
}
