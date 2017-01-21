#include "pickupManager.h"

// Apparently, cannot declare this in the same namespace that PICKUP_TYPE was defined
std::unordered_map<std::string, pickupNS::PICKUP_TYPE> nameToEnum({
	{ "MAGNET", pickupNS::PICKUP_TYPE::MAGNET },
	{ "INVERT", pickupNS::PICKUP_TYPE::INVERT }
});

PickupManager::PickupManager() {}

PickupManager::~PickupManager() {}

void PickupManager::initialize(PickupJson pickupJson) {
	std::unordered_map<pickupNS::PICKUP_TYPE, Pickup*> pickupsMap;
	std::vector<PickupData*> pickupDataVec = pickupJson.pickupDataVec;
	PickupData* dataPtr = NULL;
	Pickup* pickupPtr = NULL;
	pickupNS::PICKUP_TYPE pickupType;

	// store all pickup info into pickupManager
	for (size_t i = 0; i < pickupDataVec.size(); i++) {
		dataPtr = new PickupData();
		dataPtr = pickupDataVec[i];
		pickupType = nameToEnum[dataPtr->name];

		pickupPtr = new Pickup(pickupType, dataPtr->frame, dataPtr->duration);
		pickupsMap.insert(typePickupPair(pickupType, pickupPtr));
	}

	pickups = pickupsMap;
}

Pickup* createPickup(pickupNS::PICKUP_TYPE pickupType) {

}