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

	enum SIDE { LEFT, RIGHT };
}

class Paddle : public Entity {
private:
	PaddleControls controls;
	int score;
	paddleNS::SIDE side;
public:	
	Paddle();
	Paddle(PaddleControls pc, paddleNS::SIDE s);

	~Paddle();
	
	// getters
	int getScore() { return score; }
	paddleNS::SIDE getSide() { return side; }

	// setters
	void setScore(int s) { score = s; }
	void setSide(paddleNS::SIDE s) { side = s; }

	void update(float frameTime);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager);
};

#endif
