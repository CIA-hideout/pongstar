#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(Graphics* g, PaddleControls pc, paddleNS::SIDE s, bool ec) : Entity() {
	entityType = entityNS::PADDLE;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;

	currentFrame = (s == paddleNS::LEFT) ? 0 : 1;
	loop = false;

	controls = pc;
	side = s;
	yVelocityMultipler = 1.0f;
	shield = false;
	magnetised = false;
	magnetBall = nullptr;
	magnetTimer = 1.0f;
	enableControls = ec;
	inverted = false;

	calibrateEdges();

	D3DXCreateLine(g->get3Ddevice(), &shieldLine);
	shieldLine->SetWidth(20);
	
	// Only work on bg, use image
	D3DXCreateLine(g->get3Ddevice(), &magnetLine);
	magnetLine->SetWidth(5);
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

	if (magnetInitialized)
		magnetTimer -= frameTime;

	if (enableControls) {
		float yVelocity = 0.0f;

		if (input->isKeyDown(controls.up)) {
			if (getY() > TOP_WALL) {	// paddle is below the top wall
				yVelocity = -paddleNS::VELOCITY * yVelocityMultipler;
			}
		}

		if (input->isKeyDown(controls.down)) {
			if (getY() + (paddleNS::HEIGHT * getScaleY()) < BOTTOM_WALL) {	// paddle is above the bottom wall
				yVelocity = paddleNS::VELOCITY * yVelocityMultipler;
			}
		}

		setVelocity(VECTOR2(0, yVelocity));

		if (magnetised && magnetBall != nullptr) {
			magnetBall->setVelocity(VECTOR2(0, yVelocity));
		}

		spriteData.x += frameTime * velocity.x;
		spriteData.y += frameTime * velocity.y;
	}
}

bool Paddle::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {	
			case entityNS::BALL: {				
				if (magnetised && !magnetInitialized) {
					initMagnetEffect(ent);
					audio->playCue(MAGNETISED_CUE);
				}	
			} break;
			
			case entityNS::BUMPER:
			case entityNS::PICKUP:
			case entityNS::PADDLE:
			default: 
				break;
		}
		return true;
	}

	return false;
}

void Paddle::runEffects() {
	Message* msgPtr;

	// initialize all effects once
	while (effects->getStartEffectQueue().size() > 0) {
		EffectDuration ed = effects->getStartEffectQueue().front();
		switch (ed.effectType) {
			case effectNS::ENLARGE: {
				spriteData.scale.y = 2.0f;
				float height =  spriteData.height * spriteData.scale.y;

				if (spriteData.y + height > BOTTOM_WALL)
					spriteData.y = (float)BOTTOM_WALL - height;
			} break;

			case effectNS::SHRINK: {
				spriteData.scale.y = 0.5f;
			} break;

			case effectNS::INVERT: {
				controls = PaddleControls(controls.down, controls.up);
				inverted = true;
			} break;

			case effectNS::BOOST: {
				yVelocityMultipler = 2.0f;
			} break;

			case effectNS::SLOW: {
				yVelocityMultipler = 0.5f;
			} break;

			case effectNS::MULTIPLY: {
				msgPtr = new Message(messageNS::RUN_EFFECT, messageNS::BALL, effectNS::MULTIPLY, -1);
				pushMsg(msgPtr);
			} break;

			case effectNS::MYSTERY: {
			} break;

			case effectNS::SHIELD: {
				// Notify balls
				shield = true;
				msgPtr = new Message(messageNS::RUN_EFFECT, messageNS::BALL, effectNS::SHIELD, id);
				pushMsg(msgPtr);
			} break;

			case effectNS::MAGNET: {
				if (!magnetised) {
					magnetTimer = ed.duration;
					magnetised = true;	
				}
			} break;

			default:
				break;
		}

		effects->popStartEffectQueue();
	}

	while (effects->getEndEffectQueue().size() > 0) {
		EffectDuration ed = effects->getEndEffectQueue().front();
		switch (ed.effectType) {
			case effectNS::ENLARGE:
			case effectNS::SHRINK: {
				spriteData.scale.y = 1.0f;
			} break;

			case effectNS::BOOST: 
			case effectNS::SLOW: {
				yVelocityMultipler = 1.0f;
			} break;

			case effectNS::INVERT:{ 
				controls = PaddleControls(controls.down, controls.up);
				inverted = false;
			} break;

			case effectNS::MULTIPLY:
			case effectNS::MYSTERY:
			case effectNS::SHIELD:
			case effectNS::MAGNET:
			default:
				break;
		}

		effects->popEndEffectQueue();
	}

	if (magnetTimer <= 0) {
		audio->playCue(HIT_CUE);
		magnetBall->setMagnetised(false);

		magnetTimer = 1.0f;
		magnetInitialized = false;
		magnetised = false;
		magnetBall = nullptr;
	}
}

void Paddle::initMagnetEffect(Entity& ent) {
	magnetBall = (Ball*)&ent;
	magnetBall->setVelocity(VECTOR2(0, 0));
	magnetBall->setMagnetised(true);
	magnetInitialized = true;

	float ballWidth = magnetBall->getWidth() * magnetBall->getScaleX();
	float paddleWidth = spriteData.width * spriteData.scale.x;

	float ballHeight = magnetBall->getHeight() * magnetBall->getScaleY();
	float paddleHeight = spriteData.height * spriteData.scale.y;

	bool collideLeft = magnetBall->getX() + ballWidth > spriteData.x;
	bool collideRight = magnetBall->getX() - ballWidth < spriteData.x; 
	bool collideTop = magnetBall->getY() + ballHeight > spriteData.y && magnetBall->getY() < spriteData.y;
	bool collideBottom = magnetBall->getY() < spriteData.y + paddleHeight && magnetBall->getY() + ballHeight > spriteData.y + paddleHeight;

	if (collideLeft && side == paddleNS::RIGHT)
		magnetBall->setX(spriteData.x - paddleWidth);
	else if (collideRight && side == paddleNS::LEFT)
		magnetBall->setX(spriteData.x + paddleWidth);
	else if (collideTop)
		magnetBall->setY(spriteData.y - ballHeight);
	else if (collideBottom)
		magnetBall->setY(spriteData.y + paddleHeight);
}

void Paddle::draw(COLOR_ARGB color) {
	Entity::draw(color);

	if (shield) {
		VECTOR2 shieldPoints[2];
		if (side == paddleNS::LEFT) {
			shieldPoints[0] = VECTOR2((float)LEFT_SHIELD, 0);
			shieldPoints[1] = VECTOR2((float)LEFT_SHIELD, (float)GAME_HEIGHT);
			shieldLine->Begin();
			shieldLine->Draw(shieldPoints, 2, graphicsNS::ORANGE & graphicsNS::ALPHA25);
		}
		else {
			shieldPoints[0] = VECTOR2((float)RIGHT_SHIELD, 0);
			shieldPoints[1] = VECTOR2((float)RIGHT_SHIELD, (float)GAME_HEIGHT);
			shieldLine->Begin();
			shieldLine->Draw(shieldPoints, 2, graphicsNS::BLUE & graphicsNS::ALPHA25);
		}

		shieldLine->End();
	}

	if (magnetised) {
		VECTOR2 magnetPoints[2];

		if (side == paddleNS::LEFT) {
			magnetPoints[0] = VECTOR2(spriteData.x - 10, spriteData.y);
			magnetPoints[1] = VECTOR2(spriteData.x - 10, spriteData.y + spriteData.height * spriteData.scale.y);
		}
		else {
			magnetPoints[0] = VECTOR2(spriteData.x + spriteData.width + 10, spriteData.y);
			magnetPoints[1] = VECTOR2(spriteData.x + spriteData.width + 10, spriteData.y + spriteData.height * spriteData.scale.y);
		}

		magnetLine->Begin();
		magnetLine->Draw(magnetPoints, 2, graphicsNS::WHITE);
		magnetLine->End();
	}
}

void Paddle::resetEffects() {
	Entity::resetEffects();

	shield = false;
	magnetised = false;	
}

/*
 * Paddle AI
 */

void Paddle::logAction(paddleNS::ACTION a) {
	char actionStr[10];

	if (a == paddleNS::UP)
		sprintf(actionStr, "UP");
	else if (a == paddleNS::DOWN)
		sprintf(actionStr, "DOWN");
	else
		sprintf(actionStr, "STAY");

	printf("[PADDLE AI] %s\n", actionStr);
}

float Paddle::moveUp() {
	if (getY() > TOP_WALL) {	// paddle is below the top wall
		return -paddleNS::VELOCITY * yVelocityMultipler;
	}

	return 0.0f;
}

float Paddle::moveDown() {
	if (getY() + (paddleNS::HEIGHT * getScaleY()) < BOTTOM_WALL) {
		return paddleNS::VELOCITY * yVelocityMultipler;
	}

	return 0.0f;
}

paddleNS::ACTION Paddle::convertNoToAction(int no) {
	if (no == 0)
		return paddleNS::UP;
	if (no == 1)
		return paddleNS::DOWN;
	return paddleNS::STAY;
}

bool Paddle::entLevelWithPaddle(float centerEntY, float centerPaddleY) {
	float height = spriteData.height * spriteData.scale.y;

	float paddleBottom = centerPaddleY + height / 2;
	float paddleTop = centerPaddleY - height / 2 ;

	return centerEntY < paddleBottom && centerEntY > paddleTop;
}

void Paddle::findNewMove(Entity* ent) {
	paddleNS::ACTION action;
	float subTimer = 1.0f / paddleNS::PARTS_OF_SECOND;
	bool entBelow = ent->getCenterY() > getCenterY();

	if (entLevelWithPaddle(ent->getCenterY(), getCenterY()))
		action = paddleNS::STAY;
	else if (entBelow)
		action = paddleNS::DOWN;
	else // entAbove 
		action = paddleNS::UP;

	if (inverted) {
		if (randBool() && action != prevAction) {
			if (action == paddleNS::UP)
				action = paddleNS::DOWN;
			else if (action == paddleNS::DOWN)
				action = paddleNS::UP;
		}
	}

	actions.push(paddleNS::ActionDuration(action, subTimer));
}

void Paddle::initMagnetAI() {
	float subTimer = magnetTimer / paddleNS::INIT_MAGNET_STEPS;
	
	for (int i = 0; i < paddleNS::INIT_MAGNET_STEPS; i++) {
		paddleNS::ACTION action = convertNoToAction(randInt(0, 2));		
		magnetActions.push(paddleNS::ActionDuration(action, subTimer));
	}
}

float Paddle::resolveActionQueue(std::queue<paddleNS::ActionDuration>* aq, float frameTime) {
	aq->front().duration -= frameTime;
	float yVelocity = 0.0f;

	logAction(aq->front().action);
	switch (aq->front().action) {
	case paddleNS::UP:
		yVelocity = moveUp();
		break;
	case paddleNS::DOWN:
		yVelocity = moveDown();
		break;
	case paddleNS::STAY:
		yVelocity = 0.0f;
		break;
	default:
		break;
	}

	if (aq->front().duration <= 0) {
		prevAction = aq->front().action;
		aq->pop();
	}
	
	return yVelocity;
}

void Paddle::ai(float frameTime, Entity &ent) {
	float yVelocity;

	if (actions.size() == 0)
		findNewMove(&ent);

	yVelocity = resolveActionQueue(&actions, frameTime);

	if (ent.getEntityType() == entityNS::BALL) {
		if (magnetised && magnetBall != nullptr) {
			if (magnetActions.size() == 0)
				initMagnetAI();

			yVelocity = resolveActionQueue(&magnetActions, frameTime);
			magnetBall->setY(magnetBall->getY() + frameTime * yVelocity);
		}
	}

	setVelocity(VECTOR2(0, yVelocity));
	spriteData.y += frameTime * velocity.y;
}
