#ifndef _TIMEATTACK_H
#define _TIMEATTACK_H

#include <chrono>

#include "pongstarBase.h"

using namespace std::chrono;

class TimeAttack : public PongstarBase {
private:
	steady_clock::time_point startTime;
	int elapsedTime;
	bool timeStarted;

public:
	TimeAttack(Game *g, DataManager* dm, FontManager* fm, TextureManagerMap t);
	~TimeAttack();

	void update(float frameTime);
	void render();
};

#endif