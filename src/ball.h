#ifndef _BALL_H
#define _BALL_H

#include "entity.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const float VELOCITY = 800.0f;
}

class Ball : public Entity {
private:
public:
	Ball();
	~Ball();

	void update(float frameTime);
	void wallCollision();
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
};

#endif
