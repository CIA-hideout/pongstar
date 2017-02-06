#include "bumper.h"

Bumper::Bumper() : Entity() {
	entityType = entityNS::BUMPER;
	spriteData.width = bumperNS::WIDTH;
	spriteData.height = bumperNS::HEIGHT;
	edge.top = -(long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.bottom = (long)(bumperNS::HEIGHT  * spriteData.scale / 2);
	edge.left = -(long)(bumperNS::WIDTH  * spriteData.scale / 2);
	edge.right = (long)(bumperNS::WIDTH  * spriteData.scale / 2);
	
	side = randBool() ? bumperNS::LEFT : bumperNS::RIGHT;
	randomLocationBumper();
}

Bumper::~Bumper() {}

int Bumper::getRandXSpawn() {
	return randInt(0, GAME_WIDTH / 4 - (int)(spriteData.width * spriteData.scale));
}

int Bumper::getRandYSpawn() {
	return randInt(TOP_WALL, BOTTOM_WALL - (int)(spriteData.height * spriteData.scale));
}

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
				//randomLocationBumper();
				break;
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
