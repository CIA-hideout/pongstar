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
	Message* msgPtr;

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
		case messageNS::OTHERS: {
			dispatchOthers(msg);
		}
		default: break;
	}
}

void MessageManager::dispatchScore(Message* msg) {
	switch (msg->getScoreCmd()) {
		case messageNS::INCREMENT: {
			paddleNS::SIDE side = (msg->getTargetType() == messageNS::LEFT_P) ? paddleNS::LEFT : paddleNS::RIGHT;
			Paddle* paddlePtr = entityManager->getPaddle(side);
			paddlePtr->setScore(paddlePtr->getScore() + 1);

			if (entityManager->getBallCount() > 1) {
				entityManager->deleteBall(msg->getEntityId());
			} else {
				// If only 1 ball in play and ball is reset to center
				// Launch ball towards winner at random angle
				Ball* b = (Ball*)entityManager->getEntity(msg->getEntityId());
				int angle = randInt(60, 120);
				VECTOR2 velocity = entityManager->getVelocityFromAngle((float)angle, ballNS::VELOCITY);

				if (side == paddleNS::LEFT) {
					velocity.x *= -1;
				}

				b->setVisible(true);
				b->autoStartBall(velocity);
			}
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
		default:
			break;
	}
}

// Modifies entities directly
void MessageManager::dispatchRunEffect(Message* msg) {
	switch (msg->getEffectType()) {
		case effectNS::MULTIPLY: {
			if (msg->getEntityId() == -1) {		// If message sent from paddle
				std::vector<Ball*> balls = entityManager->getBalls();

				for (size_t i = 0; i < balls.size(); ++i) {
					entityManager->multiplyBall(balls[i]->getId());
				}
			} else {
				entityManager->multiplyBall(msg->getEntityId());
			}

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

void MessageManager::dispatchOthers(Message* msg) {
	switch (msg->getOthersCmd()) {
		case messageNS::CLEAN_UP: {
			std::vector<Ball*> balls = entityManager->getBalls();

			if (balls.size() == 1) {
				std::vector<Paddle*> paddles = entityManager->getPaddles();
				for (size_t i = 0; i < paddles.size(); i++) {
					paddles[i]->resetEffects();
				}
			}
		} break;
		default: break;
	}
}
