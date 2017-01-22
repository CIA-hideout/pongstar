#ifndef _PICKUP_H
#define _PICKUP_H

#include <unordered_map>

#include "entity.h"

namespace pickupNS {
	const enum EFFECT_TYPE { MAGNET, INVERT };
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 9;
	const float VELOCITY = 1000.0f;
}

class Pickup : public Entity {
private:
	pickupNS::EFFECT_TYPE effectType;
	float duration;
public:
	Pickup();
	Pickup(pickupNS::EFFECT_TYPE et, int f, float d);

	~Pickup();

	// getters
	pickupNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }

	// setters
	void setEffectType(pickupNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }

	void update(float frameTime);
};

#endif