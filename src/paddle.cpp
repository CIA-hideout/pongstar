#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(PaddleControls pc, paddleNS::SIDE s) : Entity() {
	entityType = entityNS::PADDLE;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge.top = -(long)(paddleNS::HEIGHT * spriteData.scale / 2);
	edge.bottom = (long)(paddleNS::HEIGHT * spriteData.scale / 2);
	edge.left = -(long)(paddleNS::WIDTH * spriteData.scale / 2);
	edge.right = (long)(paddleNS::WIDTH * spriteData.scale / 2);

	controls = pc;
	side = s;

	currentFrame = (side == paddleNS::LEFT) ? 0 : 1;
	loop = false;
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

	float yVelocity = 0.0f;
	
	if (input->isKeyDown(controls.up)) {
		if (getY() > TOP_WALL) {
			yVelocity = -paddleNS::VELOCITY;
		}
	}

	if (input->isKeyDown(controls.down)) {
		if (getY() + paddleNS::HEIGHT < BOTTOM_WALL) {
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