#ifndef _PICKUPMANAGER_H
#define _PICKUPMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "graphics.h"
#include "gameError.h"
#include "textureManager.h"
#include "dataManager.h"
#include "pickup.h"
#include "game.h"

typedef std::pair<pickupNS::PICKUP_TYPE, PickupData*> typePickupDataPair;

class PickupManager {
private:
	TextureManager pickupTexture;
	std::unordered_map<pickupNS::PICKUP_TYPE, PickupData*> pickupDataMap;
public:
	PickupManager();
	~PickupManager();

	void initialize(Graphics* graphics, PickupJson pickupJson);
	Pickup* createPickup(Game* game, pickupNS::PICKUP_TYPE pickupType);
};

#endif