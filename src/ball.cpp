#include "ball.h"

Ball::Ball() : Entity() {
	entityType = entityNS::BALL;
	spriteData.width = ballNS::WIDTH;
	spriteData.height = ballNS::HEIGHT;
	edge.top = -(long)(ballNS::HEIGHT * spriteData.scale / 2);
	edge.bottom = (long)(ballNS::HEIGHT * spriteData.scale / 2);
	edge.left = -(long)(ballNS::WIDTH * spriteData.scale / 2);
	edge.right = (long)(ballNS::WIDTH * spriteData.scale / 2);
}

Ball::~Ball() {}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	if (velocity.x == 0 && velocity.y == 0) {
		if (input->wasKeyPressed(SPACE_KEY)) {
			velocity.x = randBool() ? ballNS::VELOCITY : -ballNS::VELOCITY;
		}
	}

	wallCollision();
}

void Ball::resetBall() {
	velocity = VECTOR2(0, 0);

	spriteData.x = GAME_WIDTH / 2 - ballNS::WIDTH / 2;
	spriteData.y = GAME_HEIGHT / 2 - ballNS::HEIGHT / 2;
}

void Ball::wallCollision() {
	Message* msgPtr = NULL;

	// Collision with right wall
	if (spriteData.x > RIGHT_WALL - ballNS::WIDTH * spriteData.scale) {
		msgPtr = new Message(messageNS::SCORE, messageNS::LEFT_P, messageNS::INCREMENT);
		setMessage(msgPtr);
		resetBall();
	}
	// Collision with left wall
	else if (spriteData.x < LEFT_WALL) {
		msgPtr = new Message(messageNS::SCORE, messageNS::RIGHT_P, messageNS::INCREMENT);
		setMessage(msgPtr);
		resetBall();
	}

	// Collision with bottom wall
	if (spriteData.y > BOTTOM_WALL - ballNS::HEIGHT * spriteData.scale) {
		spriteData.y = BOTTOM_WALL - ballNS::HEIGHT * spriteData.scale;
		velocity.y = -velocity.y;
	}
	// Collision with top wall
	else if (spriteData.y < TOP_WALL) {
		spriteData.y = TOP_WALL;
		velocity.y = -velocity.y;
	}
}

void Ball::bumperCollision(Entity &bumper, VECTOR2 &collisionVector) {
	// Get positive values of collision vector
	float xCollisionValue = (collisionVector.x >= 0) ? collisionVector.x : -collisionVector.x;
	float yCollisionValue = (collisionVector.y >= 0) ? collisionVector.y : -collisionVector.y;

	// Collided on left or right face
	if (xCollisionValue > yCollisionValue) {
		velocity.x = -velocity.x;
	}
	// Collided on top or bottom face
	else if (xCollisionValue < yCollisionValue) {
		velocity.y = -velocity.y;
	}
	// Collided precisely at the corner (xCollisionValue = yCollisionValue)
	else {
		VECTOR2 newVelocity = VECTOR2(-velocity.y, -velocity.x);
		velocity = newVelocity;
	}
}

void Ball::runEffects() {
	Message* msgPtr = NULL;

	if (effects->getEffects().size() > 0) {
		for (std::pair<effectNS::EFFECT_TYPE, float> currentEffect : effects->getEffects()) {
			switch (currentEffect.first) {
				case effectNS::ENLARGE: {
					spriteData.scale = (currentEffect.second == 0) ? 1.0f : 2.0f;
				} break;
				
				case effectNS::MULTIPLY: {
					msgPtr = new Message(messageNS::RUN_EFFECT, messageNS::BALL, effectNS::MULTIPLY);
					setMessage(msgPtr);
				} break;
			}

			if (currentEffect.second == 0)
				effects->removeEffect(currentEffect.first);
		}
	}
}

bool Ball::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
			case entityNS::PADDLE: {
				Entity::paddleBounce(collisionVector, ent, ballNS::VELOCITY);
			} break;

			case entityNS::BUMPER: {
				bumperCollision(ent, collisionVector);
			} break;

			default: break;
		}
	}

	return true;
}

void Ball::addEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	effects->addEffect(effectType, duration);
}


float Ball::getBallAngle() {
	float theta = (90 * fabs(velocity.y)) / ballNS::VELOCITY;
	float angle = 0;

	if (velocity.x >= 0 && velocity.y < 0) {
		angle = theta;
	}
	else if (velocity.x > 0 && velocity.y >= 0) {
		angle = 90 + theta;
	}
	else if (velocity.x <= 0 && velocity.y > 0) {
		angle = 180 + theta;
	}
	else if (velocity.x < 0 && velocity.y <= 0) {
		angle = 270 + theta;
	}

	return angle;
}