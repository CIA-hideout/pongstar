#include "messageManager.h"

MessageManager::MessageManager() {}

MessageManager::MessageManager(PickupManager* pm, EntityManager* em) {
	pickupManager = pm;
	entityManager = em;
}

MessageManager::~MessageManager() {}

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
	printf("score msg %d\n", msg->getEntityId());
	switch (msg->getScoreCmd()) {
		case messageNS::INCREMENT: {
			Paddle* paddlePtr = msg->getTargetType() == messageNS::LEFT_P ? 
				entityManager->getPaddle(paddleNS::LEFT) : entityManager->getPaddle(paddleNS::RIGHT);
			paddlePtr->setScore(paddlePtr->getScore() + 1);

			entityManager->deleteBall(msg->getEntityId());
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
			entityManager->getEntity(msg->getEntityId())->addEffect(msg->getEffectType(), msg->getDuration());
		} break;
	}
}

void MessageManager::dispatchRunEffect(Message* msg) {
	switch (msg->getEffectType()) {
		case effectNS::MULTIPLY: {
			Ball* currentBall = (Ball*)entityManager->getEntity(msg->getEntityId());
			float ballAngle = currentBall->getBallAngle();
			VECTOR2 newVelocity;

			Ball* newBall1 = entityManager->createBall();
			newBall1->setX(currentBall->getX());
			newBall1->setY(currentBall->getY());
			newVelocity = entityManager->getVelocityFromAngle(ballAngle + 30);
			newBall1->setVelocity(newVelocity);

			Ball* newBall2 = entityManager->createBall();
			newBall2->setX(currentBall->getX());
			newBall2->setY(currentBall->getY());
			newVelocity = entityManager->getVelocityFromAngle(ballAngle - 30);
			newBall2->setVelocity(newVelocity);
		} break;

		default: break;
	}
}