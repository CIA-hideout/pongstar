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
	Message* msgPtr = nullptr;
	messageNS::TARGET_TYPE targetType;

	if (Entity::collidesWith(ent, collisionVector)) {
		if (ent.getEntityType() == entityNS::BALL) {
			switch (getEffectType()) {
				case effectNS::MULTIPLY:
				case effectNS::BOOST:
					targetType = messageNS::BALL;
					break;
			}
		}
		else if (ent.getEntityType() == entityNS::PADDLE) {
			switch (getEffectType()) {
				case effectNS::MULTIPLY:
					targetType = messageNS::BALL;
					break;

				case effectNS::BOOST:
					targetType = (ent.getX() >= GAME_WIDTH / 2) ? messageNS::RIGHT_P : messageNS::LEFT_P;
					break;
			}
		}

		setActive(false);
		msgPtr = new Message(messageNS::ADD_EFFECT, targetType, effectType, duration);
		setMessage(msgPtr);
	}

	return true;
}

void Pickup::checkWithinView() {
	if (spriteData.x < LEFT_WALL - (spriteData.width * spriteData.scale) || spriteData.x > RIGHT_WALL) {
		setActive(false);
	}
}