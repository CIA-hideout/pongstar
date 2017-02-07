#ifndef _PADDLE_H
#define _PADDLE_H

#include "entity.h"
#include "dataManager.h"
#include "graphics.h"

namespace paddleNS {
	const int HEIGHT = 120;
	const int WIDTH = 20;
	const int NCOLS = 2;
	const int SIDE_SPACE = 60;
	const float VELOCITY = 400.0f;

	enum SIDE { LEFT, RIGHT };
}

class Paddle : public Entity {
private:
	PaddleControls controls;
	int score;
	paddleNS::SIDE side;
	bool shield;
	bool boosted;
	bool slowed;
	bool inverted;
	bool magnetised;

	LP_LINE shieldLine;

public:	
	Paddle();
	Paddle(Graphics* g, PaddleControls pc, paddleNS::SIDE s);

	~Paddle();

	void draw(COLOR_ARGB color);
	
	// getters
	int getScore() { return score; }
	paddleNS::SIDE getSide() { return side; }
	bool getShieldOn() { return shield; }

	// setters
	void setScore(int s) { score = s; }
	void setSide(paddleNS::SIDE s) { side = s; }
	void setShield(bool s) { shield = s; }

	void update(float frameTime);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	void runEffects();
};

#endif
