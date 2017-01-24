#include "messageManager.h"

MessageManager::MessageManager() {}

MessageManager::MessageManager(std::vector<Entity*>* ev) {
	entityVector = ev;
}

MessageManager::~MessageManager() {}

Paddle* MessageManager::getPaddle(paddleNS::SIDE side) {
	Paddle* paddlePtr = NULL;

	for (size_t i = 0; i < entityVector->size(); i++) {
		if ((*entityVector)[i]->getEntityType() == entityNS::PADDLE) {
			paddlePtr = (Paddle*)(*entityVector)[i];
			
			if (paddlePtr->getSide() == side) {
				return paddlePtr;
			}
		}
	}

	return new Paddle();
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
	}
}

void MessageManager::dispatchScore(Message* msg) {
	switch (msg->getCmdNo()) {
		case 1: {
			Paddle* paddlePtr = msg->getTargetType() == messageNS::LEFT_P ? getPaddle(paddleNS::LEFT) : getPaddle(paddleNS::RIGHT);
			paddlePtr->setScore(paddlePtr->getScore() + 1);
		} break;
	}
}
