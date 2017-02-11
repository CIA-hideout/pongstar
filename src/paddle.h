#ifndef _PADDLE_H
#define _PADDLE_H

#include <queue>

#include "entity.h"
#include "dataManager.h"
#include "graphics.h"
#include "ball.h"

namespace paddleNS {
	const int HEIGHT = 120;
	const int WIDTH = 20;
	const int NCOLS = 2;
	const int SIDE_SPACE = 60;
	const float VELOCITY = 1000.0f;

	enum SIDE { LEFT, RIGHT };
	enum ACTION {
		UP, DOWN, STAY
	};
	
	struct ActionDuration {
		ACTION action;
		float duration;

		ActionDuration() {}
		ActionDuration(ACTION a, float d) : action(a), duration(d) {}
	};

	const int INIT_MAGNET_STEPS = 8;
	const int PARTS_OF_SECOND = 6;
	const int LEVEL_BUFFER_RANGE = 50;
}

class Paddle : public Entity {
private:
	PaddleControls controls;
	paddleNS::SIDE side;
	int score;

	float yVelocityMultipler;
	bool shield;
	bool magnetised;

	Ball* magnetBall;
	float magnetTimer;
	bool magnetInitialized;

	LP_LINE shieldLine;
	LP_LINE magnetLine;

	// AI
	std::queue<paddleNS::ActionDuration> magnetActions;
	std::queue<paddleNS::ActionDuration> actions;

public:
	Paddle();
	Paddle(Graphics* g, PaddleControls pc, paddleNS::SIDE s);

	~Paddle();

	void draw(COLOR_ARGB color);

	// getters
	PaddleControls getControls() { return controls; }
	int getScore() { return score; }
	paddleNS::SIDE getSide() { return side; }
	bool getShield() { return shield; }
	bool getMagnetised() { return magnetised; }
	Ball* getMagnetBall() { return magnetBall; }
	float getMagnetTimer() { return magnetTimer; }
	bool getMagnetInitialized() { return magnetInitialized; }

	// setters
	void setPaddleControls(PaddleControls pc) { controls = pc; }
	void setScore(int s) { score = s; }
	void setSide(paddleNS::SIDE s) { side = s; }
	void setShield(bool s) { shield = s; }
	void setMagnetised(bool m) { magnetised = m; }
	void setMagnetBall(Ball* mb) { magnetBall = mb; }
	void setMagnetTimer(float mt) { magnetTimer = mt; }
	void setMagnetInitialized(bool mi) { magnetInitialized = mi; }

	void update(float frameTime);
	void ai(float frameTime, Entity &ent);
	bool collidesWith(Entity& ent, VECTOR2& collisionVector);

	void runEffects();
	void resetEffects();
	void startMagnetTimer() { magnetInitialized = true; };
	void initMagnetEffect(Entity& ent);

	// AI
	float moveUp();
	float moveDown();
	paddleNS::ACTION convertNoToAction(int n);
	void findNewMove(Ball* b);
	void initMagnetAI();
	float resolveActionQueue(std::queue<paddleNS::ActionDuration>* aq, 
		float frameTime);
	bool ballLevelWithPaddle(int centerBallY, int centerPaddleY);
	void logAction(paddleNS::ACTION a);
};

#endif
