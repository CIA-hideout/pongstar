#include "messageManager.h"

MessageManager::MessageManager() {}

MessageManager::MessageManager(PickupManager* pm, BallManager* bm, std::vector<Entity*>* ev) {
	entityVector = ev;
	pickupManager = pm;
	ballManager = bm;
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
	Message* msgPtr = nullptr;

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
		case messageNS::PICKUP: {
			dispatchPickup(msg);
		} break;
		case messageNS::ADD_EFFECT: {
			dispatchAddEffect(msg);
		} break;
		case messageNS::RUN_EFFECT: {
			dispatchRunEffect(msg);
		} break;
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

void MessageManager::dispatchPickup(Message* msg) {
	Pickup* pickup = pickupManager->randomPickup();
	pickup->setVelocity(
		msg->getPickupCmd() == messageNS::MOVE_LEFT ? 
		VECTOR2(-pickupNS::VELOCITY, 0) :
		VECTOR2(pickupNS::VELOCITY, 0)
	);
}

void MessageManager::dispatchAddEffect(Message* msg) {
	switch (msg->getTargetType()) {
		case messageNS::BALL: {
			getBall()->addEffect(msg->getEffectType(), msg->getDuration());
		} break;
	}
}

void MessageManager::dispatchRunEffect(Message* msg) {
	switch (msg->getEffectType()) {
		case effectNS::MULTIPLY: {
			Ball* currentBall = getBall();
			float ballAngle = currentBall->getBallAngle();
			VECTOR2 newVelocity;

			Ball* newBall1 = ballManager->createBall();
			newBall1->setX(currentBall->getX());
			newBall1->setY(currentBall->getY());
			newVelocity = ballManager->getVelocityFromAngle(ballAngle + 30);
			newBall1->setVelocity(newVelocity);

			Ball* newBall2 = ballManager->createBall();
			newBall2->setX(currentBall->getX());
			newBall2->setY(currentBall->getY());
			newVelocity = ballManager->getVelocityFromAngle(ballAngle - 30);
			newBall2->setVelocity(newVelocity);
		} break;

		default: break;
	}
}