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

	effectNS::EffectData data = effectDataNS::effectArray[randomInt(rng)];
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, &pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	return pickup;
}
