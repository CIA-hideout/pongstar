#ifndef _BALLMANAGER_H
#define _BALLMANAGER_H

#include "ball.h"
#include "textureManager.h"

class BallManager {
private:
	Game* game;
	TextureManager* ballTexture;
	std::vector<Entity*>* entityVector;

public:
	BallManager();
	BallManager(Game* g, TextureManager* bt, std::vector<Entity*>* ev);

	~BallManager();

	Ball* createBall();
	VECTOR2 getVelocityFromAngle(float angle);
};

#endif