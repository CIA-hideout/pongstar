#ifndef _BUMPER_H
#define _BUMPER_H

#include "entity.h"

namespace bumperNS {
	const int HEIGHT = 100;
	const int WIDTH = 100;
	const int NCOLS = 1;
	const enum SIDE { LEFT, RIGHT };
}

class Bumper : public Entity {
private:
	std::uniform_int_distribution<int> randomBumperX;
	std::uniform_int_distribution<int> randomBumperY;
	bumperNS::SIDE side;

public:
	Bumper();
	~Bumper();

	bumperNS::SIDE getSide() { return side; }
	void setSide(bumperNS::SIDE s) { side = s; }

	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	void randomLocationBumper();
};

#endif