#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>

#include "util/random.h"
#include "game.h"
#include "gameError.h"
#include "textureManager.h"
#include "entityManager.h"
#include "entity.h"
#include "pickup.h"

namespace effectDataNS {
	const effectNS::EffectData effectArray[] = {
		effectNS::EffectData(effectNS::MAGNET, 0, 1.0f),
		effectNS::EffectData(effectNS::INVERT, 1, 0.0f),
		effectNS::EffectData(effectNS::SHIELD, 2, 0.0f),
		effectNS::EffectData(effectNS::MULTIPLY, 3, 0.0f),
		effectNS::EffectData(effectNS::BOOST, 4, 3.0f),
		effectNS::EffectData(effectNS::SLOW, 5, 3.0f),
		effectNS::EffectData(effectNS::SHRINK, 6, 1.0f),
		effectNS::EffectData(effectNS::ENLARGE, 7, 3.0f),
		effectNS::EffectData(effectNS::MYSTERY, 8, 1.0f)
	};

	const int EFFECT_ARR_SIZE = 9;
}

class PickupManager {
private:
	Game* game;
	TextureManager* pickupTexture;
	EntityManager* entityManager;

public:
	PickupManager();
	PickupManager(Game* g, TextureManager* pt, EntityManager* em);

	~PickupManager();

	int getRandYSpawn();
	int getRandEffectArrIndex();

	Pickup* randomPickup();
	Pickup* createPickup(effectNS::EFFECT_TYPE et);

	effectNS::EffectData getPickupData(effectNS::EFFECT_TYPE et);
};

#endif
