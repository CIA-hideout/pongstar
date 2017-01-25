#ifndef _PICKUP_H
#define _PICKUP_H

#include "entity.h"

namespace pickupNS {
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 9;
	const float VELOCITY = 1000.0f;
	const float SCALE = 0.4f;
}

class Pickup : public Entity {
private:
	effectNS::EFFECT_TYPE effectType;
	float duration;

public:
	Pickup();
	Pickup(effectNS::EFFECT_TYPE et, int f, float d);

	~Pickup();

	// getters
	effectNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }

	// setters
	void setEffectType(effectNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }

	void update(float frameTime);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager);
};

#endif
