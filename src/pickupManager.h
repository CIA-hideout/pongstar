#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <unordered_map>
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
	const effectNS::EffectData effectArray[] = {
		effectNS::EffectData(effectNS::MAGNET, 0, 1.0f),
		effectNS::EffectData(effectNS::INVERT, 1, 1.0f)
	};

	const int EFFECT_ARR_SIZE = 2;
}

class PickupManager {
private:
	TextureManager pickupTexture;

public:
	PickupManager();
	PickupManager(Graphics* graphics);

	~PickupManager();

	Pickup* randomPickup(Game* game);
};

#endif