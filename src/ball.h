#ifndef _BALL_H
#define _BALL_H

#include "util/random.h"
#include "entity.h"
#include "message.h"
#include "pickup.h"
#include "bumper.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const float VELOCITY = 800.0f;
}

class Ball : public Entity {
private:
	bool leftShield;
	bool rightShield;

public:
	Ball();
	~Ball();

	void setLeftShield(bool s) { leftShield = s; };
	void setRightShield(bool s) { rightShield = s; }

	bool getLeftShield() { return leftShield; }
	bool getRightShield() { return rightShield; }

	void update(float frameTime);
	void resetBall();
	void wallCollision();
	void bumperCollision(Entity &bumper, VECTOR2 &collisionVector);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	
	void runEffects();

	float getBallAngle();
};

#endif