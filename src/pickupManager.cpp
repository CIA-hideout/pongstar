#include "pickupManager.h"

// Apparently, cannot declare this in the same namespace that PICKUP_TYPE was defined
std::unordered_map<std::string, pickupNS::PICKUP_TYPE> nameToEnum({
	{ "MAGNET", pickupNS::PICKUP_TYPE::MAGNET },
	{ "INVERT", pickupNS::PICKUP_TYPE::INVERT }
});

PickupManager::PickupManager() {}

PickupManager::~PickupManager() {}

void PickupManager::initialize(Graphics* graphics, PickupJson pickupJson) {
	std::vector<PickupData*> pickupDataVec = pickupJson.pickupDataVec;
	PickupData* dataPtr = NULL;
	pickupNS::PICKUP_TYPE pickupType;

	// store all pickup info into pickupManager
	for (size_t i = 0; i < pickupDataVec.size(); i++) {
		dataPtr = pickupDataVec[i];
		pickupType = nameToEnum[dataPtr->name];

		pickupDataMap.insert(typePickupDataPair(pickupType, dataPtr));
	}

	if (!pickupTexture.initialize(graphics, PICKUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup texture"));
}

Pickup* PickupManager::createPickup(Game* game, pickupNS::PICKUP_TYPE pickupType) {
	PickupData* data = pickupDataMap[pickupType];
	Pickup* pickup = new Pickup(pickupType, data->frame, data->duration);
	
	if (!pickup->initialize(game, pickupNS::WIDTH, pickupNS::HEIGHT, pickupNS::NCOLS, &pickupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pickup"));

	return pickup;
}
