#ifndef _BALL_H
#define _BALL_H

#include <cmath>
#include "entity.h"
#include "message.h"
#include "pickup.h"
#include "bumper.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const float VELOCITY = 200.0f;
	const float AUTO_START_DELAY = 0.5f;
}

class Ball : public Entity {
private:
	bool autoStart;
	float autoStartTimer;
	VECTOR2 autoStartVelocity;

	bool leftShield;
	bool rightShield;
	bool magnetised;

public:
	Ball();
	~Ball();

	void setLeftShield(bool s) { leftShield = s; };
	void setRightShield(bool s) { rightShield = s; }
	void setMagnetised(bool m) { magnetised = m; }

	bool getLeftShield() { return leftShield; }
	bool getRightShield() { return rightShield; }
	bool getMagnetised() { return magnetised; }

	void update(float frameTime);
	void resetBall();
	void autoStartBall(VECTOR2 velocity);
	void randomStartBall();
	void wallCollision();
	void bumperCollision(Entity &bumper, VECTOR2 &collisionVector);
	void paddleBounce(VECTOR2 &collisionVector, Entity &ent);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	
	void runEffects();

	float getBallVelocity();
	float getBallAngle();
};

#endif