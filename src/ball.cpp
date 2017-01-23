#include "ball.h"

// RNG
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> randomBool(0, 1);


Ball::Ball() : Entity() {
	entityType = entityNS::BALL;
	spriteData.width = ballNS::WIDTH;
	spriteData.height = ballNS::HEIGHT;
	edge.top = -ballNS::HEIGHT * spriteData.scale / 2;
	edge.bottom = ballNS::HEIGHT * spriteData.scale / 2;
	edge.left = -ballNS::WIDTH * spriteData.scale / 2;
	edge.right = ballNS::WIDTH * spriteData.scale / 2;
}

Ball::~Ball() {}

void Ball::update(float frameTime) {
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	if (velocity.x == 0 && velocity.y == 0) {
		if (input->wasKeyPressed(SPACE_KEY)) {
			velocity.x = (randomBool(rng) == 1) ? ballNS::VELOCITY : -ballNS::VELOCITY;
		}
	}

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