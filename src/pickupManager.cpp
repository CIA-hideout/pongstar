#include "pickupManager.h"

PickupManager::PickupManager() {}

PickupManager::PickupManager(Game* g, TextureManager* pt, std::vector<Entity*>* ev) {
	game = g;
	pickupTexture = pt;
	entityVector = ev;
}

PickupManager::~PickupManager() {}

int PickupManager::getRandYSpawn() {
	return randInt(TOP_WALL, BOTTOM_WALL - (int)(pickupNS::HEIGHT * pickupNS::SCALE));
}

int PickupManager::getRandEffectArrIndex() {
	return randInt(0, effectDataNS::EFFECT_ARR_SIZE);
}

Pickup* PickupManager::randomPickup() {
	effectNS::EffectData data = effectDataNS::effectArray[getRandEffectArrIndex()];
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	pickup->setX(GAME_WIDTH / 2 - (pickupNS::WIDTH * pickupNS::SCALE) / 2);
	pickup->setY((float)getRandYSpawn());

	entityVector->push_back(pickup);
	return pickup;
}

// For testing
Pickup* PickupManager::createPickup(effectNS::EFFECT_TYPE et) {
	effectNS::EffectData data = getPickupData(et);
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	pickup->setX(GAME_WIDTH * 3 / 4);
	pickup->setY(GAME_HEIGHT / 2 - (pickupNS::HEIGHT * pickupNS::SCALE) / 2);
	
	entityVector->push_back(pickup);
	return pickup;
}

effectNS::EffectData PickupManager::getPickupData(effectNS::EFFECT_TYPE et) {
	for (int i = 0; i < effectDataNS::EFFECT_ARR_SIZE; i++) {
		if (effectDataNS::effectArray[i].effectType ==  et)
			return effectDataNS::effectArray[i];
	}

	return effectNS::EffectData();
}
