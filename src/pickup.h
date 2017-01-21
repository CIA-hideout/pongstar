#ifndef _PICKUP_H
#define _PICKUP_H

#include <unordered_map>

#include "entity.h"

namespace pickupNS {
	const enum PICKUP_TYPE { MAGNET, INVERT };
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 9;
	const float VELOCITY = 1000.0f;
}

class Pickup : public Entity {
private:
	pickupNS::PICKUP_TYPE pickupType;
	float duration;
public:
	Pickup();
	Pickup(pickupNS::PICKUP_TYPE pt, int f, float d);

	~Pickup();

	// getters
	pickupNS::PICKUP_TYPE getPickupType() { return pickupType; }
	float getDuration() { return duration; }

	// setters
	void setPickupType(pickupNS::PICKUP_TYPE pt) { pickupType = pt; }
	void setDuration(float d) { duration = d; }

	void update(float frameTime);
};

#endif