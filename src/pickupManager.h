#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>

#include "random.h"
#include "game.h"
#include "gameError.h"
#include "textureManager.h"
#include "entity.h"
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
	Game* game;
	TextureManager* pickupTexture;
	std::vector<Entity*>* entityVector;

public:
	PickupManager();
	PickupManager(Game* g, TextureManager* pt, std::vector<Entity*>* ev);

	~PickupManager();
	
	int getRandYSpawn();
	int getRandEffectArrIndex();

	Pickup* randomPickup();
	Pickup* createPickup(effectNS::EFFECT_TYPE et);

	effectNS::EffectData getPickupData(effectNS::EFFECT_TYPE et);
};

#endif
