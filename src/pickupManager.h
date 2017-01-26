#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>
#include <random>

#include "game.h"
#include "graphics.h"
#include "gameError.h"
#include "textureManager.h"
#include "pickup.h"

namespace effectDataNS {
	const effectNS::EffectData effectArray[] = {
		effectNS::EffectData(effectNS::MAGNET, 0, 1.0f),
		effectNS::EffectData(effectNS::INVERT, 1, 1.0f),
		effectNS::EffectData(effectNS::SHIELD, 2, 1.0f),
		effectNS::EffectData(effectNS::MULTIPLY, 3, 1.0f),
		effectNS::EffectData(effectNS::BOOST, 4, 1.0f),
		effectNS::EffectData(effectNS::SLOW, 5, 1.0f),
		effectNS::EffectData(effectNS::SHRINK, 6, 1.0f),
		effectNS::EffectData(effectNS::ENLARGE, 7, 3.0f),
		effectNS::EffectData(effectNS::MYSTERY, 8, 1.0f)
	};

	const int EFFECT_ARR_SIZE = 9;
}


class PickupManager {
private:
	TextureManager pickupTexture;

public:
	PickupManager();
	PickupManager(Graphics* graphics);

	~PickupManager();

	Pickup* randomPickup(Game* game);
	Pickup* createPickup(Game* game, effectNS::EFFECT_TYPE et);

	effectNS::EffectData getPickupData(effectNS::EFFECT_TYPE et);
};

#endif
