#include "ball.h"

// RNG
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> randomBool(0, 1);

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
			velocity.x = (randomBool(rng) == 1) ? ballNS::VELOCITY : -ballNS::VELOCITY;
		}
	}

	wallCollision();
}

void Ball::wallCollision() {
	if (spriteData.x > GAME_WIDTH - ballNS::WIDTH * spriteData.scale) {
		spriteData.x = GAME_WIDTH - ballNS::WIDTH * spriteData.scale;
		velocity.x = -velocity.x;
	}
	else if (spriteData.x < 0) {
		spriteData.x = 0;
		velocity.x = -velocity.x;
	}
	if (spriteData.y > GAME_HEIGHT - ballNS::HEIGHT * spriteData.scale) {
		spriteData.y = GAME_HEIGHT - ballNS::HEIGHT * spriteData.scale;
		velocity.y = -velocity.y;
	}
	else if (spriteData.y < 0) {
		spriteData.y = 0;
		velocity.y = -velocity.y;
	}
}

void Ball::runEffects(EffectManager &effectManager) {
	if (effectManager.getCurrentEffects(id).size() > 0) {
		for (std::pair<effectNS::EFFECT_TYPE, float> currentEffect : effectManager.getCurrentEffects(id)) {
			switch (currentEffect.first) {
			case effectNS::ENLARGE:
				float scale = 2.0f;

				if (currentEffect.second == 0) {
					scale = 1.0f;
					effectManager.removeEffect(id, currentEffect.first);
				}

				spriteData.scale = scale;
				break;
			}
		}
	}
}

bool Ball::collidesWith(Entity &ent, VECTOR2 &collisionVector, EffectManager &effectManager) {
	if (Entity::collidesWith(ent, collisionVector, effectManager)) {
		switch (ent.getEntityType()) {
		case entityNS::PADDLE:
		case entityNS::BUMPER:
			Entity::paddleBounce(collisionVector, ent, ballNS::VELOCITY);
			break;
		}
	}

	return true;
}