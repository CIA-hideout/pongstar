#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>

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
		effectNS::EffectData(effectNS::INVERT, 1, 3.0f),
		effectNS::EffectData(effectNS::SHIELD, 2, 0.0f),
		effectNS::EffectData(effectNS::MULTIPLY, 3, 0.0f),
		effectNS::EffectData(effectNS::BOOST, 4, 3.0f),
		effectNS::EffectData(effectNS::SLOW, 5, 3.0f),
		effectNS::EffectData(effectNS::SHRINK, 6, 3.0f),
		effectNS::EffectData(effectNS::ENLARGE, 7, 3.0f),
		effectNS::EffectData(effectNS::MYSTERY, 8, 1.0f)
	};

	const int EFFECT_ARR_SIZE = 9;
	const float TESTING_X_VELOCITY = 300.0f;
}

class PickupManager {
private:
	Game* game;
	TextureManager* pickupTexture;
	EntityManager* entityManager;
	IntFloatMap* pickupDelayTimers;

	bool effectTesting;
	effectNS::EFFECT_TYPE effectToTest;

public:
	PickupManager();
	PickupManager(Game* g, TextureManager* pt, EntityManager* em, IntFloatMap* pdt);

	~PickupManager();

	int getRandYSpawn();
	int getRandEffectArrIndex();

	Pickup* randomPickup();
	Pickup* createPickup(effectNS::EFFECT_TYPE et);
	std::vector<Pickup*> getPickups();

	effectNS::EffectData getPickupData(effectNS::EFFECT_TYPE et);

	void testPickup(effectNS::EFFECT_TYPE et);
	void massSpawnPickups();
	void massSpawnPickups(int side);
	void massSpawnPickups(std::vector<effectNS::EFFECT_TYPE> ev);
	void massSpawnContrastPickups();
};

#endif
