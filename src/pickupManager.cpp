#include "pickupManager.h"

// Apparently, cannot declare this in the same namespace that EFFECT_TYPE was defined
std::unordered_map<std::string, pickupNS::EFFECT_TYPE> nameToEnum({
	{ "MAGNET", pickupNS::EFFECT_TYPE::MAGNET },
	{ "INVERT", pickupNS::EFFECT_TYPE::INVERT }
});

PickupManager::PickupManager() {}

PickupManager::~PickupManager() {}

void PickupManager::initialize(Graphics* graphics, PickupJson pickupJson) {
	std::vector<PickupData*> pickupDataVec = pickupJson.pickupDataVec;
	PickupData* dataPtr = NULL;
	pickupNS::EFFECT_TYPE effectType;

	// store all pickup info into pickupManager
	for (size_t i = 0; i < pickupDataVec.size(); i++) {
		dataPtr = pickupDataVec[i];
		effectType = nameToEnum[dataPtr->name];

		pickupDataMap.insert(pickupDataPair(effectType, dataPtr));
	}

	if (!pickupTexture.initialize(graphics, PICKUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup texture"));
}

Pickup* PickupManager::createPickup(Game* game, pickupNS::EFFECT_TYPE effectType) {
	PickupData* data = pickupDataMap[effectType];
	Pickup* pickup = new Pickup(effectType, data->frame, data->duration);
	
	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, &pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	return pickup;
}
