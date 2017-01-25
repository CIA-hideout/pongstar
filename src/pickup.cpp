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

void Pickup::update(float frameTime) {}

bool Pickup::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	Message* msgPtr = NULL;

	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL: {
			setActive(false);
			msgPtr = new Message(messageNS::EFFECT, messageNS::BALL, effectType, duration);
			setMessage(msgPtr);
		}	break;
		}
	}

	return true;
}