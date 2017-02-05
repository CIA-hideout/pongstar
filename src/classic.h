#ifndef _CLASSIC_H
#define _CLASSIC_H

#include "pongstarBase.h"

namespace classicNS {
	const int POINTS_TO_WIN = 2;
}

class Classic : public PongstarBase {
private:

public:
	Classic(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t);
	~Classic();

	void update(float frameTime);
};

#endif