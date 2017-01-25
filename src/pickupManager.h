#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>
#include <random>

#include "graphics.h"
#include "gameError.h"
#include "textureManager.h"
#include "pickup.h"
#include "game.h"

namespace effectDataNS {
	const effectNS::EffectData effectArray[] = {
		effectNS::EffectData(effectNS::MAGNET, 0, 1.0f),
		effectNS::EffectData(effectNS::INVERT, 1, 1.0f),
		effectNS::EffectData(effectNS::ENLARGE, 7, 2.0f)
	};

	const int EFFECT_ARR_SIZE = 3;
}


class PickupManager {
private:
	TextureManager pickupTexture;

	effectNS::EffectData getPickupData(effectNS::EFFECT_TYPE et);
public:
	PickupManager();
	PickupManager(Graphics* graphics);

	~PickupManager();

	Pickup* randomPickup(Game* game);
	Pickup* createPickup(Game* game, effectNS::EFFECT_TYPE et);

};

#endif
