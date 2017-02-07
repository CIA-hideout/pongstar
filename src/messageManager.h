/*	In charge of relaying messages to the correct entites or components
	MessageManager should not store any data
*/

#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H

#include <queue>

#include "message.h"
#include "entity.h"
#include "paddle.h"
#include "ball.h"
#include "pickupManager.h"

namespace messageManagerNS {
	const float MAGNET_DELAY_TIMER = 1.0f;
}

class MessageManager {
private:
	Game* game;
	std::queue<Message*> messageQueue;

	float magnetDelayTimer;
	bool startedTimer;
	int magnetiseBallId;

	// Components
	EntityManager* entityManager;
	PickupManager* pickupManager;

public:
	MessageManager();
	MessageManager(PickupManager* pm, EntityManager* em);
	~MessageManager();

	void push(Message* msg);
	void dispatch(Message* msg);

	void dispatchScore(Message* msg);
	void dispatchPickup(Message* msg);
	void dispatchAddEffect(Message* msg);
	void dispatchRunEffect(Message* msg);
	void dispatchEndEffect(Message* msg);
	void dispatchMagnetEffect(Message* msg);
	void dispatchOthers(Message* msg);

	void update(float frameTime);
	
	void resolve();
};

#endif