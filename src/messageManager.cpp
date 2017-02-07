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
		case messageNS::END_EFFECT: {
			dispatchEndEffect(msg);
		} break;
		case messageNS::MAGNET_EFFECT: {
			dispatchMagnetEffect(msg);
		} break;
		default: break;
	}
}

void MessageManager::dispatchScore(Message* msg) {
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
	// id here is the collided entity id, !pickupId
	switch (msg->getTargetType()) {
		case messageNS::BALL: {
			entityManager->getEntity(msg->getEntityId())->addEffect(msg->getEffectType(), msg->getDuration());
		} break;
		case messageNS::BOTH_P: {
			std::vector<Paddle*> pv = entityManager->getPaddles();
			for (size_t i = 0; i < pv.size(); i++) {
				pv[i]->addEffect(msg->getEffectType(), msg->getDuration());
			}
		} break;
		case messageNS::LEFT_P: {
			entityManager->getPaddle(paddleNS::LEFT)->addEffect(msg->getEffectType(), msg->getDuration());
		} break;
		case messageNS::RIGHT_P: {
			entityManager->getPaddle(paddleNS::RIGHT)->addEffect(msg->getEffectType(), msg->getDuration());
		} break;
	}
}

// Modifies entities directly
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

		case effectNS::SHIELD: {
			// Identify sending msg id, left or right paddle
			Paddle* p = (Paddle*)entityManager->getEntity(msg->getEntityId());
			paddleNS::SIDE side = p->getSide();

			// get all balls
			std::vector<Ball*> bv = entityManager->getBalls();

			for (size_t i = 0; i < bv.size(); i++) {
				if (side == paddleNS::LEFT)
					bv[i]->setLeftShield(true);
				else
					bv[i]->setRightShield(true);
			}
		} break;

		case effectNS::MAGNET: {
			// Identify sending msg id, left or right paddle
			Paddle* p = (Paddle*)entityManager->getEntity(msg->getEntityId());
			//paddleNS::SIDE side = p->getSide();

			// get all balls
			std::vector<Ball*> bv = entityManager->getBalls();

			for (size_t i = 0; i < bv.size(); i++) {
				bv[i]->setMagnetised(true);
			}
		} break;
		
		case effectNS::MAGNET: {

		}

		default: break;
	}
}

// Modifies entities directly
void MessageManager::dispatchEndEffect(Message* msg) {
	switch (msg->getEffectType()) {
		case effectNS::SHIELD: {
			// Identify paddle target that shield has been hit

			Paddle* p = msg->getTargetType() ==
				messageNS::LEFT_P ?
				entityManager->getPaddle(paddleNS::LEFT) :
				entityManager->getPaddle(paddleNS::RIGHT);

			p->setShield(false);

			// notify balls that shield is off
			std::vector<Ball*> bv = entityManager->getBalls();
			for (size_t i = 0; i < bv.size(); i++) {
				if (p->getSide() == paddleNS::LEFT)
					bv[i]->setLeftShield(false);
				else
					bv[i]->setRightShield(false);
			}

		} break;

		default: break;
	}
}

// Modifies entities directly
void MessageManager::dispatchMagnetEffect(Message* msg) {
	int paddleId = msg->getPaddleId();
	int ballId = msg->getBallId();

	Paddle* p = (Paddle*)entityManager->getEntity(paddleId);
	Ball* b = (Ball*)entityManager->getEntity(ballId);

	switch (msg->getMagnetCmd()) {
	case messageNS::BIND: {
		p->setMagnetBall(b);

		// notifies other balls to stop listening

	} break;
	case messageNS::UNBIND: {
		p->setMagnetised(false);
		p->setMagnetBall(nullptr);
		b->setMagnetised(false);
	} break;
	default: break;
	}
}
