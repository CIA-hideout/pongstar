#ifndef _PADDLE_H
#define _PADDLE_H

#include "entity.h"

namespace paddleNS {
	const int HEIGHT = 120;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const int SIDE_SPACE = 60;
}

class Paddle : public Entity {
private:
public:
	Paddle();
	~Paddle();

	void update(float frameTime);
};

#endif