#ifndef _CLASSIC_H
#define _CLASSIC_H

#include "pongstarBase.h"

class Classic : public PongstarBase {
private:

public:
	Classic(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t);
	~Classic();
};

#endif