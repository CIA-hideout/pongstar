#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(Graphics* g, PaddleControls pc, paddleNS::SIDE s) : Entity() {
	entityType = entityNS::PADDLE;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge.top = -(long)(paddleNS::HEIGHT * spriteData.scale.y / 2);
	edge.bottom = (long)(paddleNS::HEIGHT * spriteData.scale.y / 2);
	edge.left = -(long)(paddleNS::WIDTH * spriteData.scale.x / 2);
	edge.right = (long)(paddleNS::WIDTH * spriteData.scale.x / 2);

	currentFrame = (s == paddleNS::LEFT) ? 0 : 1;
	loop = false;

	controls = pc;
	side = s;
	yVelocityMultipler = 1.0f;
	shield = false;
	magnetised = false;
	magnetBall = nullptr;
	magnetTimer = 1.0f;

	D3DXCreateLine(g->get3Ddevice(), &shieldLine);
	shieldLine->SetWidth(20);
	
	// Only work on bg, use image
	D3DXCreateLine(g->get3Ddevice(), &magnetLine);
	magnetLine->SetWidth(5);
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

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

	if (magnetInitialized) {
		magnetTimer -= frameTime;
	}

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}

bool Paddle::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {	
			case entityNS::BALL: {
				if (magnetised && !magnetInitialized)
					initMagnetEffect(ent);
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
				int height =  spriteData.height * spriteData.scale.y;

				if (spriteData.y + height > BOTTOM_WALL)
					spriteData.y = BOTTOM_WALL - height;
			} break;

			case effectNS::SHRINK: {
				spriteData.scale.y = 0.5f;
			} break;

			case effectNS::INVERT: {
				controls = PaddleControls(controls.down, controls.up);
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

void Paddle::initMagnetEffect(Entity &ent) {
	audio->playCue(HIT_CUE);
	magnetBall = (Ball*)&ent;
	magnetBall->setVelocity(VECTOR2(0, 0));
	magnetBall->setMagnetised(true);
	magnetInitialized = true;
	
	int ballWidth = magnetBall->getWidth() * magnetBall->getScaleX();
	int paddleWidth = spriteData.width * spriteData.scale.x;

	// Ball will always stick to the front of paddle
	if (magnetBall->getX() + ballWidth > spriteData.x && side == paddleNS::RIGHT) {
		magnetBall->setX(spriteData.x - paddleWidth);
	} 
	else if (magnetBall->getX() - ballWidth < spriteData.x + paddleWidth && side == paddleNS::LEFT) {
		magnetBall->setX(spriteData.x + paddleWidth);
	}
}

void Paddle::draw(COLOR_ARGB color) {
	Entity::draw(color);

	if (shield) {
		VECTOR2 shieldPoints[2];
		if (side == paddleNS::LEFT) {
			shieldPoints[0] = VECTOR2(LEFT_SHIELD, 0);
			shieldPoints[1] = VECTOR2(LEFT_SHIELD, GAME_HEIGHT);
			shieldLine->Begin();
			shieldLine->Draw(shieldPoints, 2, graphicsNS::ORANGE + graphicsNS::ALPHA25);
		}
		else {
			shieldPoints[0] = VECTOR2(RIGHT_SHIELD, 0);
			shieldPoints[1] = VECTOR2(RIGHT_SHIELD, GAME_HEIGHT);
			shieldLine->Begin();
			shieldLine->Draw(shieldPoints, 2, graphicsNS::BLUE + graphicsNS::ALPHA25);
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