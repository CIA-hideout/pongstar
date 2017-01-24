#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>
#include <random>

#include "graphics.h"
#include "gameError.h"
#include "textureManager.h"
#include "dataManager.h"
#include "pickup.h"
#include "game.h"

namespace effectDataNS {
	const EffectData effectArray[] = {
		EffectData(effectNS::MAGNET, 0, 1.0f),
		EffectData(effectNS::INVERT, 1, 1.0f)
		EffectData(effectNS::ENLARGE, 7, 5.0f)
	};

	const int EFFECT_ARR_SIZE = 2;
}

class PickupManager {
private:
	TextureManager pickupTexture;

	EffectData getPickupData(effectNS::EFFECT_TYPE et);
public:
	PickupManager();
	PickupManager(Graphics* graphics);

	~PickupManager();

	Pickup* randomPickup(Game* game);
	Pickup* createPickup(Game* game, effectNS::EFFECT_TYPE et);

};

#endif
