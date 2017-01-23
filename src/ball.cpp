#include "ball.h"

Ball::Ball() : Entity() {
	entityType = entityNS::BALL;
	spriteData.width = ballNS::WIDTH;
	spriteData.height = ballNS::HEIGHT;
	edge.top = -ballNS::HEIGHT / 2;
	edge.bottom = ballNS::HEIGHT / 2;
	edge.left = -ballNS::WIDTH / 2;
	edge.right = ballNS::WIDTH / 2;
}

Ball::~Ball() {}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	wallCollision();
}

void Ball::wallCollision() {
	if (spriteData.x > GAME_WIDTH - ballNS::WIDTH) {
		spriteData.x = GAME_WIDTH - ballNS::WIDTH;
		velocity.x = -velocity.x;
	}
	else if (spriteData.x < 0) {
		spriteData.x = 0;
		velocity.x = -velocity.x;
	}
	if (spriteData.y > GAME_HEIGHT - ballNS::HEIGHT) {
		spriteData.y = GAME_HEIGHT - ballNS::HEIGHT;
		velocity.y = -velocity.y;
	}
	else if (spriteData.y < 0) {
		spriteData.y = 0;
		velocity.y = -velocity.y;
	}
}

bool Ball::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
		case entityNS::PADDLE:
			Entity::paddleBounce(collisionVector, ent, ballNS::VELOCITY);
			break;
		}
	}

	return true;
}