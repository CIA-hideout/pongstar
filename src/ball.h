#ifndef _BALL_H
#define _BALL_H

#include "entity.h"
#include "message.h"
#include "pickup.h"
#include "bumper.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const float VELOCITY = 800.0f;
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
	bool initializedMagnetEffect;
public:
	Ball();
	~Ball();

	void setLeftShield(bool s) { leftShield = s; };
	void setRightShield(bool s) { rightShield = s; }
	void setMagnetised(bool m) { magnetised = m; }
	void setInitializedMagnetEffect(bool ime) { initializedMagnetEffect = ime; }

	bool getLeftShield() { return leftShield; }
	bool getRightShield() { return rightShield; }
	bool getMagnetised() { return magnetised; }
	bool getInitializedMagnetEffect() { return initializedMagnetEffect; }

	void update(float frameTime);
	void resetBall();
	void autoStartBall(VECTOR2 velocity);
	void randomStartBall();
	void wallCollision();
	void bumperCollision(Entity &bumper, VECTOR2 &collisionVector);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector);
	
	void runEffects();
	void initMagnetEffect(int targetPaddleId);
	void resetMagnetBinding();

	float getBallAngle();
};

#endif