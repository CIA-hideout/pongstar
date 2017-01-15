#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(PaddleControls pc) {
	controls = pc;
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

	float yVelocity = 0.0f;

	if (input->isKeyDown(controls.up)) {
		yVelocity = -paddleNS::VELOCITY;
	}

	if (input->isKeyDown(controls.down)) {
		yVelocity = paddleNS::VELOCITY;
	}

	setVelocity(VECTOR2(0, yVelocity));

	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
}
