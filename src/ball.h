#ifndef _BALL_H
#define _BALL_H

#include "entity.h"
#include "message.h"
#include "effectTimer.h"
#include "pickup.h"

namespace ballNS {
	const int HEIGHT = 20;
	const int WIDTH = 20;
	const int NCOLS = 1;
	const float VELOCITY = 800.0f;
}

class Ball : public Entity {
private:
	EffectTimer* effectTimer;
public:
	Ball();
	~Ball();

	void update(float frameTime);
	void resetBall();
	void wallCollision();
	void runEffects(EffectManager &effectManager);
	bool collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager);
	// bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	void triggerEffect(effectNS::EFFECT_TYPE et);
};

#endif
