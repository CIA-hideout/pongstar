#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);
}
