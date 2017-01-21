#ifndef _PICKUP_H
#define _PICKUP_H

#include <unordered_map>

#include "entity.h"

namespace pickupNS {
	enum PICKUP_TYPE { MAGNET, INVERT };
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 9;
	const float VELOCITY = 1000.0f;
}

class Pickup : public Entity {
private:
	pickupNS::PICKUP_TYPE pickupType;
	int frame;
	float duration;
public:
	Pickup();
	Pickup(pickupNS::PICKUP_TYPE pt, int f, float d);

	~Pickup();

	void update(float frameTime);
};

#endif