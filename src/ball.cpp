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

void Ball::runEffects() {
	if (effectManager->getEffects().size() > 0) {
		for (std::pair<effectNS::EFFECT_TYPE, float> currentEffect : effectManager->getEffects()) {
			switch (currentEffect.first) {
			case effectNS::ENLARGE:
				float scale = 2.0f;

				if (currentEffect.second == 0) {
					scale = 1.0f;
					effectManager->removeEffect(currentEffect.first);
				}

				spriteData.scale = scale;
				break;
			}
		}
	}
}

bool Ball::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::PADDLE:
		case entityNS::BUMPER:
			Entity::paddleBounce(collisionVector, ent, ballNS::VELOCITY);
			break;
		}
	}

	return true;
}

void Ball::triggerEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	effectManager->addEffect(effectType, duration);
}
