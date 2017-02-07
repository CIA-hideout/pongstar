#include "paddle.h"

Paddle::Paddle() : Entity() {}

Paddle::Paddle(Graphics* g, PaddleControls pc, paddleNS::SIDE s) : Entity() {
	entityType = entityNS::PADDLE;
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge.top = -(long)(paddleNS::HEIGHT * spriteData.scale / 2);
	edge.bottom = (long)(paddleNS::HEIGHT * spriteData.scale / 2);
	edge.left = -(long)(paddleNS::WIDTH * spriteData.scale / 2);
	edge.right = (long)(paddleNS::WIDTH * spriteData.scale / 2);

	controls = pc;
	side = s;

	currentFrame = (side == paddleNS::LEFT) ? 0 : 1;
	loop = false;

	D3DXCreateLine(g->get3Ddevice(), &shieldLine);
	shieldLine->SetWidth(20);
}

Paddle::~Paddle() {}

void Paddle::update(float frameTime) {
	Entity::update(frameTime);

	float yVelocity = 0.0f;
	
	if (input->isKeyDown(controls.up)) {
		if (getY() > TOP_WALL) {
			yVelocity = -paddleNS::VELOCITY;
		}
	}

	if (input->isKeyDown(controls.down)) {
		if (getY() + paddleNS::HEIGHT < BOTTOM_WALL) {
			yVelocity = paddleNS::VELOCITY;
		}
	}

	setVelocity(VECTOR2(0, yVelocity));

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}

bool Paddle::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	if (Entity::collidesWith(ent, collisionVector)) {
		switch (ent.getEntityType()) {	
		}
	}

	return true;
}

void Paddle::runEffects() {
	Message* msgPtr = nullptr;

	if (effects->getEffects().size() > 0) {
		for (std::pair<effectNS::EFFECT_TYPE, float> currentEffect : effects->getEffects()) {
			switch (currentEffect.first) {
				case effectNS::ENLARGE: {
					spriteData.scale = (currentEffect.second == 0) ? 1.0f : 2.0f;
				} break;
				case effectNS::INVERT: {			
				} break;
				case effectNS::SHIELD: {
					// Notify balls
					shield = true;
					msgPtr = new Message(messageNS::RUN_EFFECT, messageNS::BALL, effectNS::SHIELD, id);
					setMessage(msgPtr);
				} break;
				case effectNS::MULTIPLY: {
				} break;
				case effectNS::BOOST: {
				} break;
				case effectNS::SLOW: {
				} break;
				case effectNS::SHRINK: {
				} break;
				case effectNS::MYSTERY: {
				} break;
			}

			if (currentEffect.second == 0)
				effects->removeEffect(currentEffect.first);
		}
	}
	
}

void Paddle::draw(COLOR_ARGB color) {
	if (shield) {
		VECTOR2 shieldPoints[2];
		if (side == paddleNS::LEFT) {
			shieldPoints[0] = VECTOR2(20, 0);
			shieldPoints[1] = VECTOR2(20, GAME_HEIGHT);
		}
		else {
			shieldPoints[0] = VECTOR2(GAME_WIDTH - 20, 0);
			shieldPoints[1] = VECTOR2(GAME_WIDTH - 20, GAME_HEIGHT);
		}

		shieldLine->Begin();
		shieldLine->Draw(shieldPoints, 2, graphicsNS::WHITE);
		shieldLine->End();
	}

	Entity::draw(color);
}