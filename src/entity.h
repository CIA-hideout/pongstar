#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"

class Entity : public Image {
protected:
	float velocity;

public:

	Entity();
	~Entity();

	float getVelocity() const { return velocity; }
	void setVelocity(float v) { velocity = v; }

	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	virtual void update(float frameTime);
};


#endif
