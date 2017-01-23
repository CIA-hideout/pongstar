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
	edge.top = -pickupNS::HEIGHT * spriteData.scale / 2;
	edge.bottom = pickupNS::HEIGHT * spriteData.scale / 2;
	edge.left = -pickupNS::WIDTH * spriteData.scale / 2;
	edge.right = pickupNS::WIDTH * spriteData.scale / 2;

	currentFrame = f;
	loop = false; 
}

Pickup::~Pickup() {}

void Pickup::update(float frameTime) {}

bool Pickup::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
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
			}
			break;
		}
	}

	return true;
}