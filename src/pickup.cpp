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
	messageNS::TARGET_TYPE targetType = messageNS::NONE;

	if (Entity::collidesWith(ent, collisionVector)) {
		// sound
		if (ent.getEntityType() == entityNS::BALL || ent.getEntityType() == entityNS::PADDLE) {
			if (effectType == effectNS::ENLARGE)
				audio->playCue(ENLARGE_CUE);
			else if (effectType == effectNS::SHRINK)
				audio->playCue(SHRINK_CUE);
			else if (effectType == effectNS::BOOST)
				audio->playCue(BOOST_CUE);
			else if (effectType == effectNS::SLOW)
				audio->playCue(SLOW_CUE);
			else if (effectType == effectNS::SHIELD)
				audio->playCue(SHIELD_CUE);
			else if (effectType == effectNS::MAGNET)
				audio->playCue(MAGNET_CUE);
		}

		if (ent.getEntityType() == entityNS::BALL) {
			switch (getEffectType()) {
				case effectNS::MULTIPLY:
				case effectNS::BOOST:
				case effectNS::SLOW:
				case effectNS::ENLARGE:
				case effectNS::SHRINK:
				case effectNS::INVERT:
					targetType = messageNS::BALL;
					break;
				case effectNS::MAGNET:
				case effectNS::SHIELD:
					targetType = messageNS::BOTH_P;
					break;
			}
		}
		else if (ent.getEntityType() == entityNS::PADDLE) {
			switch (getEffectType()) {
				case effectNS::MULTIPLY:
					targetType = messageNS::BALL;
					break;

				case effectNS::ENLARGE:
				case effectNS::BOOST:
				case effectNS::MAGNET:
				case effectNS::SHIELD:
					targetType = (ent.getX() >= GAME_WIDTH / 2) ? messageNS::RIGHT_P : messageNS::LEFT_P;
					break;

				case effectNS::SHRINK:
				case effectNS::SLOW:
				case effectNS::INVERT:
					targetType = (ent.getX() >= GAME_WIDTH / 2) ? messageNS::LEFT_P : messageNS::RIGHT_P;
					break;
			}
		}
		else {	// collide with other entities, ex. bumper
			return true;
		}

		setActive(false);
		msgPtr = new Message(messageNS::ADD_EFFECT, targetType, effectType, ent.getId(), duration);
		setMessage(msgPtr);
	}

	return true;
}

void Pickup::checkWithinView() {
	if (spriteData.x < LEFT_WALL - (spriteData.width * spriteData.scale) || spriteData.x > RIGHT_WALL) {
		setActive(false);
	}
}
