#include "pickupManager.h"

PickupManager::PickupManager() {}

PickupManager::PickupManager(Game* g, TextureManager* pt, EntityManager* em, IntFloatMap* pdt) {
	game = g;
	pickupTexture = pt;
	entityManager = em;
	pickupDelayTimers = pdt;

	effectTesting = false;
}

PickupManager::~PickupManager() {}

int PickupManager::getRandYSpawn() {
	return randInt(TOP_WALL, BOTTOM_WALL - (int)(pickupNS::HEIGHT * pickupNS::SCALE.y));
}

int PickupManager::getRandEffectArrIndex() {
	return randInt(0, effectDataNS::EFFECT_ARR_SIZE - 1);
}

Pickup* PickupManager::randomPickup() {
	effectNS::EffectData data;

	data = effectTesting ? getPickupData(effectToTest) : effectDataNS::effectArray[getRandEffectArrIndex()];
	if (data.effectType == effectNS::MYSTERY) {
		effectNS::EffectData random = effectDataNS::effectArray[getRandEffectArrIndex()];
		while (random.effectType == effectNS::MYSTERY) {
			random = effectDataNS::effectArray[getRandEffectArrIndex()];
		}
		data.effectType = random.effectType;
		data.duration = random.duration;
	}
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration, pickupDelayTimers);
	
	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	pickup->setX(GAME_WIDTH / 2 - (pickupNS::WIDTH * pickupNS::SCALE.x) / 2);
	pickup->setY((float)getRandYSpawn());

	entityManager->addEntity(pickup);
	return pickup;
}

// For testing
Pickup* PickupManager::createPickup(effectNS::EFFECT_TYPE et) {
	effectNS::EffectData data = getPickupData(et);
	Pickup* pickup = new Pickup(data.effectType, data.frame, data.duration, pickupDelayTimers);

	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	pickup->setX(GAME_WIDTH * 3 / 4);
	pickup->setY(GAME_HEIGHT / 2 - (pickupNS::HEIGHT * pickupNS::SCALE.y) / 2);
	
	entityManager->addEntity(pickup);
	return pickup;
}

effectNS::EffectData PickupManager::getPickupData(effectNS::EFFECT_TYPE et) {
	for (int i = 0; i < effectDataNS::EFFECT_ARR_SIZE; i++) {
		if (effectDataNS::effectArray[i].effectType ==  et)
			return effectDataNS::effectArray[i];
	}

	return effectNS::EffectData();
}

void PickupManager::testPickup(effectNS::EFFECT_TYPE et) {
	effectTesting = true;
	effectToTest = et;
}

void PickupManager::massSpawnPickups() {
	Pickup* pickup;

	for (int i = 0; i <= 10; i++) {
		pickup = randomPickup();
		pickup->setVelocity(randBool() ?
			VECTOR2(-effectDataNS::TESTING_Y_VELOCITY, 0) :
			VECTOR2(effectDataNS::TESTING_Y_VELOCITY, 0));
	}
}

void PickupManager::massSpawnPickups(int side) {
	Pickup* pickup;

	for (int i = 0; i <= 5; i++) {
		pickup = randomPickup();
		pickup->setVelocity(side == 0 ?
			VECTOR2(-effectDataNS::TESTING_Y_VELOCITY, 0) :
			VECTOR2(effectDataNS::TESTING_Y_VELOCITY, 0));
	}
}