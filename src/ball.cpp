#include "ball.h"

Ball::Ball() : Entity() {
	entityType = entityNS::BALL;
	spriteData.width = ballNS::WIDTH;
	spriteData.height = ballNS::HEIGHT;
	edge.top = -(long)(ballNS::HEIGHT * spriteData.scale.y / 2);
	edge.bottom = (long)(ballNS::HEIGHT * spriteData.scale.y / 2);
	edge.left = -(long)(ballNS::WIDTH * spriteData.scale.x / 2);
	edge.right = (long)(ballNS::WIDTH * spriteData.scale.x / 2);

	autoStart = false;
	autoStartTimer = 0.0;
	leftShield = false;
	rightShield = false;
}

Ball::~Ball() {}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	if (autoStart) {
		if (autoStartTimer < ballNS::AUTO_START_DELAY) {
			autoStartTimer += frameTime;
		} else {
			audio->playCue(HIT_CUE);
			autoStart = false;
			autoStartTimer = 0.0;
			velocity = autoStartVelocity;
		}
	}

	wallCollision();
}

void Ball::resetBall() {
	velocity = VECTOR2(0, 0);
	effects = new Effects();
	spriteData.x = GAME_WIDTH / 2 - ballNS::WIDTH / 2;
	spriteData.y = GAME_HEIGHT / 2 - ballNS::HEIGHT / 2;
	spriteData.scale = VECTOR2(1.0f, 1.0f);
}

void Ball::autoStartBall(VECTOR2 v) {
	autoStart = true;
	autoStartVelocity = v;
}

void Ball::randomStartBall() {
	velocity.x = randBool() ? ballNS::VELOCITY : -ballNS::VELOCITY;
	audio->playCue(HIT_CUE);
}

void Ball::wallCollision() {
	Message* msgPtr;

	// Collide with right wall and shield is on
	if (spriteData.x > RIGHT_SHIELD - ballNS::WIDTH * spriteData.scale.x && rightShield) {
		spriteData.x = RIGHT_SHIELD - ballNS::WIDTH * spriteData.scale.x;
		velocity.x = -velocity.x;

		// dispatch ms to turn off right shield for paddle and other balls
		msgPtr = new Message(messageNS::END_EFFECT, messageNS::RIGHT_P, effectNS::SHIELD, id);
		pushMsg(msgPtr);
	}
	// Collide with right wall
	else if (spriteData.x > RIGHT_WALL) {
		msgPtr = new Message(messageNS::SCORE, messageNS::LEFT_P, messageNS::INCREMENT, id);
		pushMsg(msgPtr);
		setVisible(false);

		// Right paddle scored, ball goes to right
		resetBall();
	}

	// Collision with left wall and shield is on
	if (spriteData.x < LEFT_SHIELD && leftShield) {
		spriteData.x = LEFT_SHIELD;
		velocity.x = -velocity.x;

		// dispatch msg to turn off left shield for paddle and other balls
		msgPtr = new Message(messageNS::END_EFFECT, messageNS::LEFT_P, effectNS::SHIELD, id);
		pushMsg(msgPtr);
	}
	// Collision with left wall
	else if (spriteData.x < LEFT_WALL - (spriteData.width * spriteData.scale.x)) {
		msgPtr = new Message(messageNS::SCORE, messageNS::RIGHT_P, messageNS::INCREMENT, id);
		pushMsg(msgPtr);
		setVisible(false);

		// Left paddle scored, ball goes to left
		resetBall();
	}

	// Collision with bottom wall
	if (spriteData.y > BOTTOM_WALL - ballNS::HEIGHT * spriteData.scale.x) {
		spriteData.y = BOTTOM_WALL - ballNS::HEIGHT * spriteData.scale.x;
		velocity.y = -velocity.y;
		audio->playCue(HIT_CUE);
	}
	// Collision with top wall
	else if (spriteData.y < TOP_WALL) {
		spriteData.y = TOP_WALL;
		velocity.y = -velocity.y;
		audio->playCue(HIT_CUE);
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

void Ball::paddleBounce(VECTOR2 &collisionVector, Entity &ent) {
	// Calculate ratios of collision vector
	float xRatio = fabs(collisionVector.x) / (fabs(collisionVector.x) + fabs(collisionVector.y));
	float yRatio = fabs(collisionVector.y) / (fabs(collisionVector.x) + fabs(collisionVector.y));
	float ballVelocity = (getResultantVelocity() == 0) ? ballNS::VELOCITY : getResultantVelocity();

	// Use ratios to determine resultant velocity of ball
	// Negative used to invert the direction
	float xVelocity = sqrt(ballVelocity * ballVelocity * xRatio);
	float yVelocity = sqrt(ballVelocity * ballVelocity * yRatio);

	if (collisionVector.x > 0) {
		xVelocity = -xVelocity;
	}
	if (collisionVector.y > 0) {
		yVelocity = -yVelocity;
	}

	velocity = VECTOR2(xVelocity, yVelocity);
}

bool Ball::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
			case entityNS::PADDLE: {
				paddleBounce(collisionVector, ent);

				if (!magnetised)
					audio->playCue(HIT_CUE);
			} break;

			case entityNS::BUMPER: {
				bumperCollision(ent, collisionVector);
				Bumper* bumper = (Bumper*)&ent;
				bumper->randomLocationBumper();
				audio->playCue(HIT_CUE);
			} break;

			default: break;
		}
		return true;
	}
	return false;
}

void Ball::runEffects() {
	Message* msgPtr;
	float xRatio, yRatio;

	// initialize all effects once
	while (effects->getStartEffectQueue().size() > 0) {
		EffectDuration ed = effects->getStartEffectQueue().front();
		switch (ed.effectType) {
		case effectNS::ENLARGE: {
			spriteData.scale = VECTOR2(2.0f, 2.0f);
			int height = spriteData.height * spriteData.scale.y;

			if (spriteData.y + height > BOTTOM_WALL)
				spriteData.y = BOTTOM_WALL - height;
		} break;

		case effectNS::SHRINK: {
			spriteData.scale = VECTOR2(0.5f, 0.5f);
		} break;

		case effectNS::INVERT: {
			velocity = VECTOR2(-velocity.x, -velocity.y);
		} break;

		case effectNS::BOOST: {
			xRatio = velocity.x / (fabs(velocity.x) + fabs(velocity.y));
			yRatio = velocity.y / (fabs(velocity.x) + fabs(velocity.y));
			velocity = VECTOR2(ballNS::VELOCITY * xRatio * 2, ballNS::VELOCITY * yRatio * 2);
		} break;

		case effectNS::SLOW: {
			xRatio = velocity.x / (fabs(velocity.x) + fabs(velocity.y));
			yRatio = velocity.y / (fabs(velocity.x) + fabs(velocity.y));
			velocity = VECTOR2(ballNS::VELOCITY * xRatio * 0.5, ballNS::VELOCITY * yRatio * 0.5);
		} break;

		case effectNS::MULTIPLY: {
			msgPtr = new Message(messageNS::RUN_EFFECT, messageNS::BALL, effectNS::MULTIPLY, id);
			pushMsg(msgPtr);
		} break;

		case effectNS::SHIELD:
		case effectNS::MAGNET:
		case effectNS::MYSTERY:
		default:
			break;
		}

		effects->popStartEffectQueue();
	}


	while (effects->getEndEffectQueue().size() > 0) {
		EffectDuration ed = effects->getEndEffectQueue().front();
		switch (ed.effectType) {
		case effectNS::ENLARGE:
		case effectNS::SHRINK: {
			spriteData.scale = VECTOR2(1.0f, 1.0f);
		} break;

		case effectNS::BOOST: {
			xRatio = velocity.x / (fabs(velocity.x) + fabs(velocity.y));
			yRatio = velocity.y / (fabs(velocity.x) + fabs(velocity.y));
			velocity = VECTOR2(ballNS::VELOCITY * xRatio, ballNS::VELOCITY * yRatio);
		} break;

		case effectNS::SLOW: {
			xRatio = velocity.x / (fabs(velocity.x) + fabs(velocity.y));
			yRatio = velocity.y / (fabs(velocity.x) + fabs(velocity.y));
			velocity = VECTOR2(ballNS::VELOCITY * xRatio, ballNS::VELOCITY * yRatio);
		} break;

		case effectNS::INVERT:
		case effectNS::MULTIPLY:
		case effectNS::MYSTERY:
		case effectNS::SHIELD:
		case effectNS::MAGNET:
		default:
			break;
		}

		effects->popEndEffectQueue();
	}
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
