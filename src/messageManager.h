/* In charge of relying messages to the correct entites or components */

#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H

#include <queue>

#include "game.h"
#include "message.h"
#include "entity.h"
#include "paddle.h"
#include "ball.h"
#include "pickupManager.h"

class MessageManager {
private:
	Game* game;
	PickupManager* pickupManager;
	std::queue<Message*> messageQueue;
	std::vector<Entity*>* entityVector;

public:
	MessageManager();
	MessageManager(Game* g, Graphics* graphics, std::vector<Entity*>* ev);
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