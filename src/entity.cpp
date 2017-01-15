#include "entity.h"

Entity::Entity() : Image() {
	velocity = 0.0f;
}

Entity::~Entity() {}

bool Entity::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	return (Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::update(float frameTime) {
	Image::update(frameTime);
}
