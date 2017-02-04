/*	In charge of relaying messages to the correct entites or components
	MessageManager should not store any data
*/

#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H

#include <queue>

#include "pickupManager.h"
#include "message.h"
#include "entity.h"
#include "paddle.h"
#include "ball.h"

class MessageManager {
private:
	std::queue<Message*> messageQueue;
	std::vector<Entity*>* entityVector;

	// Components
	PickupManager* pickupManager;

public:
	MessageManager();
	MessageManager(PickupManager* pm, std::vector<Entity*>* ev);
	~MessageManager();

	void push(Message* msg);
	void dispatch(Message* msg);

	void dispatchScore(Message* msg);
	void dispatchEffect(Message* msg);
	void dispatchPickup(Message* msg);

	void resolve();

	Paddle* getPaddle(paddleNS::SIDE s);
	Ball* getBall();
};

#endif