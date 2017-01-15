#ifndef _BALL_H
#define _BALL_H

#include "entity.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
}

class Ball : public Entity {
private:
public:
	Ball();
	~Ball();

	void update(float frameTime);
};

#endif
