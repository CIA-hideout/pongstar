#ifndef _PADDLE_H
#define _PADDLE_H

#include "entity.h"
#include "dataManager.h"

namespace paddleNS {
	const int HEIGHT = 120;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const int SIDE_SPACE = 60;
	const float VELOCITY = 400.0f;
}

class Paddle : public Entity {
private:
	PaddleControls controls;
public:	
	Paddle();
	Paddle(PaddleControls controls);

	~Paddle();

	void update(float frameTime);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
};

#endif
