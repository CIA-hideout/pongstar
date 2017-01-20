#include "pickup.h"

Pickup::Pickup() : Entity() {
	entityType = entityNS::PICKUP;
}

Pickup::~Pickup() {}

void Pickup::update(float frameTime) {}