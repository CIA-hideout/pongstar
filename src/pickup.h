#ifndef _PICKUP_H
#define _PICKUP_H

#include <unordered_map>
#include "entity.h"

namespace pickupNS {
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 9;
	const float VELOCITY = 100.0f;
	const VECTOR2 SCALE = { 0.5f, 0.5f };
	const float PICKUP_DELAY = 0.1f;
}

class Pickup : public Entity {
private:
	effectNS::EFFECT_TYPE effectType;
	float duration;
	std::unordered_map<int, float>* pickupDelayTimers;

public:
	Pickup();
	Pickup(effectNS::EFFECT_TYPE et, int f, float d, std::unordered_map<int, float>* pdt);

	~Pickup();

	// getters
	effectNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }

	// setters
	void setEffectType(effectNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }

	void update(float frameTime);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	void checkWithinView();
};

#endif
