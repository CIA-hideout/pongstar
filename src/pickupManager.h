#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "dataManager.h"
#include "pickup.h"

typedef std::pair<pickupNS::PICKUP_TYPE, Pickup*> typePickupPair;

class PickupManager {
private:
	std::unordered_map<pickupNS::PICKUP_TYPE, Pickup*> pickups;
public:
	PickupManager();
	~PickupManager();

	void initialize(PickupJson pickupJson);
	Pickup* createPickup(pickupNS::PICKUP_TYPE pickupType);
};

#endif