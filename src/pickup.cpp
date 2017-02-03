#include "pickup.h"

Pickup::Pickup() : Entity() {}

Pickup::Pickup(effectNS::EFFECT_TYPE et, int f, float d) : Entity() {
	entityType = entityNS::PICKUP;
	effectType = et;
	duration = d;

	// entity
	spriteData.scale = pickupNS::SCALE;
	spriteData.width = pickupNS::WIDTH;
	spriteData.height = pickupNS::HEIGHT;
	edge.top = -(long)(pickupNS::HEIGHT * spriteData.scale / 2);
	edge.bottom = (long)(pickupNS::HEIGHT * spriteData.scale / 2);
	edge.left = -(long)(pickupNS::WIDTH * spriteData.scale / 2);
	edge.right = (long)(pickupNS::WIDTH * spriteData.scale / 2);

	currentFrame = f;
	loop = false;
}

Pickup::~Pickup() {}

void Pickup::update(float frameTime) {
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	checkWithinView();
}

bool Pickup::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	Message* msgPtr = NULL;

	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL: {
			setActive(false);
			msgPtr = new Message(messageNS::EFFECT, messageNS::BALL, effectType, duration);
			setMessage(msgPtr);
		}	break;

		case entityNS::PADDLE: {
			setActive(false);
			messageNS::TARGET_TYPE targetType = (ent.getX() >= GAME_WIDTH / 2) ? messageNS::RIGHT_P : messageNS::LEFT_P;
			msgPtr = new Message(messageNS::EFFECT, targetType, effectType, duration);
			setMessage(msgPtr);
		}	break;
		}
	}

	return true;
}

void Pickup::checkWithinView() {
	if (spriteData.x < LEFT_WALL - (spriteData.width * spriteData.scale) || spriteData.x > RIGHT_WALL) {
		setActive(false);
	}
}