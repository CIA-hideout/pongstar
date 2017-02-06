#ifndef _BALLMANAGER_H
#define _BALLMANAGER_H

#include "ball.h"
#include "textureManager.h"

class BallManager {
private:
	Game* game;
	TextureManager* ballTexture;
	std::vector<Entity*>* entityVector;
	int ballCount;

public:
	BallManager();
	BallManager(Game* g, TextureManager* bt, std::vector<Entity*>* ev);

	~BallManager();

	int getBallCount() { return ballCount; }
	void setBallCount(int bc) { ballCount = bc; }

	Ball* createBall();
	VECTOR2 getVelocityFromAngle(float angle);
};

#endif