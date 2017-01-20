#ifndef _PICKUP_H
#define _PICKUP_H

#include "entity.h"

namespace pickupNS {
	enum PICKUP_TYPE { MAGNET, INVERT };
}

class Pickup : public Entity {
private:
	pickupNS::PICKUP_TYPE pickupType;
	int frame;
	float duration;
public:
	Pickup();
	Pickup(pickupNS::PICKUP_TYPE pt, int frame, float duration);

	~Pickup();

	void update(float frameTime);
};

#endif