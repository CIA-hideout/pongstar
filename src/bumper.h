#ifndef _BUMPER_H
#define _BUMPER_H

#include "entity.h"
#include "util/random.h"

namespace bumperNS {
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 1;
	const enum SIDE { LEFT, RIGHT };
}

class Bumper : public Entity {
private:
	bumperNS::SIDE side;

public:
	Bumper();
	~Bumper();

	int getRandXSpawn();
	int getRandYSpawn();

	bumperNS::SIDE getSide() { return side; }
	void setSide(bumperNS::SIDE s) { side = s; }

	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	void randomLocationBumper();
};

#endif