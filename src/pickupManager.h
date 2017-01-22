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

typedef std::pair<pickupNS::EFFECT_TYPE, PickupData*> pickupDataPair;

class PickupManager {
private:
	TextureManager pickupTexture;
	std::unordered_map<pickupNS::EFFECT_TYPE, PickupData*> pickupDataMap;
public:
	PickupManager();
	~PickupManager();

	void initialize(Graphics* graphics, std::vector<PickupData*> pickupVec);
	Pickup* createPickup(Game* game, pickupNS::EFFECT_TYPE effectType);
};

#endif