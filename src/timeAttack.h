#ifndef _TIMEATTACK_H
#define _TIMEATTACK_H

#include <chrono>

#include "pongstarBase.h"

using namespace std::chrono;

class TimeAttack : public PongstarBase {
private:

public:
	TimeAttack(Game *g, Audio* a, DataManager* dm, FontManager* fm, TextureManagerMap t, bool sp);
	~TimeAttack();

	void update(float frameTime);
	void render();
};

#endif