#include "pickup.h"

Pickup::Pickup() : Entity() {
}

Pickup::Pickup(pickupNS::EFFECT_TYPE et, int f, float d) : Entity() {
	entityType = entityNS::PICKUP;
	effectType = et;
	duration = d;

	// entity
	spriteData.width = pickupNS::WIDTH;
	spriteData.height = pickupNS::HEIGHT;
	edge.top = -pickupNS::HEIGHT / 2;
	edge.bottom = pickupNS::HEIGHT / 2;
	edge.left = -pickupNS::WIDTH / 2;
	edge.right = pickupNS::WIDTH / 2;

	currentFrame = f;
	loop = false; 
	spriteData.scale = 0.4f;
}

Pickup::~Pickup() {}

void Pickup::update(float frameTime) {}