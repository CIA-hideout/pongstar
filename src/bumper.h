#ifndef _BUMPER_H
#define _BUMPER_H

#include "entity.h"

namespace bumperNS {
	const int HEIGHT = 200;
	const int WIDTH = 200;
	const int NCOLS = 1;
}

class Bumper : public Entity {
private:
	std::uniform_int_distribution<int> randomBumperX;
	std::uniform_int_distribution<int> randomBumperY;

public:
	Bumper();
	~Bumper();

	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	void randomLocationBumper();
};

#endif