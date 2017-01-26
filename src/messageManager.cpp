#include "messageManager.h"

MessageManager::MessageManager() {}

MessageManager::MessageManager(Game* g, Graphics* graphics, std::vector<Entity*>* ev) {
	game = g;
	entityVector = ev;

	pickupManager = new PickupManager(graphics);
}

MessageManager::~MessageManager() {}

Paddle* MessageManager::getPaddle(paddleNS::SIDE side) {
	Paddle* paddlePtr = NULL;

	for (size_t i = 0; i < entityVector->size(); i++) {
		if ((*entityVector)[i]->getEntityType() == entityNS::PADDLE) {
			paddlePtr = (Paddle*)(*entityVector)[i];
			
			if (paddlePtr->getSide() == side)
				return paddlePtr;
		}
	}

	return new Paddle();
}

Ball* MessageManager::getBall() {
	for (size_t i = 0; i < entityVector->size(); i++) {
		if ((*entityVector)[i]->getEntityType() == entityNS::BALL)
			return (Ball*)(*entityVector)[i];
	}

	return new Ball();
}

void MessageManager::push(Message* msg) {
	messageQueue.push(msg);
}

void MessageManager::resolve() {
	Message* msgPtr = NULL;

	while (messageQueue.size() > 0) {
		msgPtr = messageQueue.front();
		dispatch(msgPtr);
		messageQueue.pop();
	}
}

void MessageManager::dispatch(Message* msg) {
	switch (msg->getMessageType()) {
		case messageNS::SCORE: {
			dispatchScore(msg);
		} break;
		case messageNS::EFFECT: {
			dispatchEffect(msg);
		} break;
		case messageNS::PICKUP: {
			dispatchPickup(msg);
		}
	}
}

void MessageManager::dispatchScore(Message* msg) {
	switch (msg->getScoreCmd()) {
		case messageNS::INCREMENT: {
			Paddle* paddlePtr = msg->getTargetType() == messageNS::LEFT_P ? getPaddle(paddleNS::LEFT) : getPaddle(paddleNS::RIGHT);
			paddlePtr->setScore(paddlePtr->getScore() + 1);
		} break;
	}
}

void MessageManager::dispatchEffect(Message* msg) {
	switch (msg->getTargetType()) {
		case messageNS::BALL: {
			getBall()->triggerEffect(msg->getEffectType(), msg->getDuration());
		} break;
	}
}

void MessageManager::dispatchPickup(Message* msg) {
	Pickup* pickup = pickupManager->randomPickup(game);

	if (msg->getPickupCmd() == messageNS::MOVE_LEFT) {
		pickup->setVelocity(VECTOR2(-pickupNS::VELOCITY, 0));
	}
	else {
		pickup->setVelocity(VECTOR2(pickupNS::VELOCITY, 0));
	}

	entityVector->push_back(pickup);
}
