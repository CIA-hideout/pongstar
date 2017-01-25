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

bool Pickup::collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager) {
	if (Entity::collidesWith(ent, collisionVector, effectManager)) {
		switch (ent.getEntityType()) {
		case entityNS::BALL:
			setActive(false);

			switch (effectType) {
			case effectNS::MAGNET:
				printf("magnet\n");
				break;

			case effectNS::INVERT:
				printf("invert\n");
				break;

			case effectNS::ENLARGE:
				printf("enlarge\n");
				effectManager.addEffect(ent.getId(), effectType, duration);
				break;
			}
			break;
		}
	}

	return true;
}