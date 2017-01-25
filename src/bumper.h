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
public:
	Bumper();
	~Bumper();

	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
};

#endif