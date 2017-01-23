#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(PaddleControls pc) : Entity() {
	entityType = entityNS::PADDLE;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge.top = -paddleNS::HEIGHT / 2;
	edge.bottom = paddleNS::HEIGHT / 2;
	edge.left = -paddleNS::WIDTH / 2;
	edge.right = paddleNS::WIDTH / 2;

	controls = pc;
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

	float yVelocity = 0.0f;

	if (input->isKeyDown(controls.up)) {
		if (getY() > 0) {
			yVelocity = -paddleNS::VELOCITY;
		}
	}

	if (input->isKeyDown(controls.down)) {
		if (getY() + paddleNS::HEIGHT < GAME_HEIGHT) {
			yVelocity = paddleNS::VELOCITY;
		}
	}

	setVelocity(VECTOR2(0, yVelocity));

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}


bool Paddle::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {
			
		}
	}

	return true;
}