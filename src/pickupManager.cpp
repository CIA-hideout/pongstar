#include "pickupManager.h"

PickupManager::PickupManager() {}

PickupManager::PickupManager(Graphics* graphics) {
	if (!pickupTexture.initialize(graphics, PICKUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup texture"));
}

PickupManager::~PickupManager() {}

Pickup* PickupManager::randomPickup(Game* game) {
	// RNG
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomInt(0, effectDataNS::EFFECT_ARR_SIZE);
	std::uniform_int_distribution<int> randomYcoord(0, GAME_HEIGHT - (int)(pickupNS::HEIGHT * pickupNS::SCALE));

	EffectData data = effectDataNS::effectArray[randomInt(rng)];
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, &pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	/*pickup->setX(GAME_WIDTH / 2 - (pickupNS::WIDTH * pickupNS::SCALE) / 2);
	pickup->setY((float)randomYcoord(rng));*/

	pickup->setX(GAME_WIDTH / 4);
	pickup->setY(GAME_HEIGHT / 2 - (pickupNS::HEIGHT * pickupNS::SCALE) / 2);

	return pickup;
}

Pickup* PickupManager::createPickup(Game* game, effectNS::EFFECT_TYPE et) {
	EffectData data = getPickupData(et);
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, &pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	return pickup;
}

EffectData PickupManager::getPickupData(effectNS::EFFECT_TYPE et) {
	for (int i = 0; i < effectDataNS::EFFECT_ARR_SIZE; i++) {
		if (effectDataNS::effectArray[i].effectType ==  et)
			return effectDataNS::effectArray[i];
	}

	return EffectData();
}
