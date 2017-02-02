#include "pongstarBase.h"

PongstarBase::PongstarBase(DataManager* dm, FontManager* fm, MessageManager* mm, TextureManagerMap t, Game* g, Input* i) {
	messageManager = mm;
	fontManager = fm;
	dataManager = dm;
	tmMap = t;
	game = g;
	input = i;
}

PongstarBase::~PongstarBase() {}

void PongstarBase::initialize(Image d) {
	divider = d;
	
	initializeEntities();

	messageManager = new MessageManager(this, graphics, &entityVector);
}

void PongstarBase::initializeEntities() {
	ControlsJson controls = dataManager->getControlsJson();

	Paddle* paddle1 = new Paddle(controls.p1, paddleNS::LEFT);
	Paddle* paddle2 = new Paddle(controls.p2, paddleNS::RIGHT);
	Ball* ball = new Ball();
	Bumper* bumper = new Bumper();

	if (!paddle1->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	if (!paddle2->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	if (!ball->initialize(game, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, tmMap[pongstarNS::BALL]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	if (!bumper->initialize(game, bumperNS::WIDTH, bumperNS::HEIGHT, bumperNS::NCOLS, tmMap[pongstarNS::BUMPER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bumper"));

	paddle1->setX((float)paddleNS::SIDE_SPACE);
	paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	paddle2->setX(GAME_WIDTH - paddleNS::SIDE_SPACE - paddleNS::WIDTH);
	paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);

	ball->setX(GAME_WIDTH / 2 - ballNS::WIDTH / 2);
	ball->setY(GAME_HEIGHT / 2 - ballNS::HEIGHT / 2);

	entityVector.push_back(paddle1);
	entityVector.push_back(paddle2);
	entityVector.push_back(ball);
	entityVector.push_back(bumper);
}

void PongstarBase::update(float frameTime) {
	for (size_t i = 0; i < entityVector.size(); ++i) {
		entityVector[i]->update(frameTime);

		if (!entityVector[i]->getActive()) {
			deleteEntityQueue.push(i);
		}

		if (entityVector[i]->getMessage() != NULL) {
			messageManager->push(entityVector[i]->getMessage());
			entityVector[i]->setMessage(NULL);
		}
	}

	while (deleteEntityQueue.size() > 0) {
		int indexToRemove = deleteEntityQueue.front();
		entityVector.erase(entityVector.begin() + indexToRemove);
		deleteEntityQueue.pop();
	}

	messageManager->resolve();

	if (input->wasKeyPressed(SPACE_KEY) && !gameStarted) {
		startTime = steady_clock::now();
		gameStarted = true;
	}

	if (gameStarted) {
		steady_clock::time_point presentTime = steady_clock::now();
		elapsedTime = duration_cast<seconds>(presentTime - startTime).count();
	}
}

void PongstarBase::ai() {

}

void PongstarBase::collisions() {
	VECTOR2 collisionVector;

	for (size_t i = 0; i < entityVector.size(); ++i) {
		for (size_t j = 0; j < entityVector.size(); ++j) {
			if (entityVector[i]->getId() != entityVector[j]->getId()) {
				entityVector[i]->collidesWith(*entityVector[j], collisionVector);
			}
		}
	}
}

void PongstarBase::render() {
	divider.draw();

	for (size_t i = 0; i < entityVector.size(); ++i) {
		entityVector[i]->draw();
	}

	std::string timeLeft = std::to_string(TIME_PER_GAME - elapsedTime);
	std::string leftPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::LEFT)->getScore());
	std::string rightPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::RIGHT)->getScore());

	printf("right %i\n", messageManager->getPaddle(paddleNS::RIGHT)->getScore());
	printf("left %i\n", messageManager->getPaddle(paddleNS::LEFT)->getScore());

	fontManager->print(
		fontNS::SABO_FILLED,
		elapsedTime > 50 ? fontNS::RED : fontNS::WHITE,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, timeLeft) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		timeLeft
		);

	fontManager->print(
		fontNS::SABO_FILLED,
		fontNS::ORANGE,
		GAME_WIDTH / 4 - fontManager->getTotalWidth(fontNS::SABO_FILLED, leftPaddleScore) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		leftPaddleScore
		);

	fontManager->print(
		fontNS::SABO_FILLED,
		fontNS::BLUE,
		GAME_WIDTH / 4 * 3 - fontManager->getTotalWidth(fontNS::SABO_FILLED, rightPaddleScore) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		rightPaddleScore
		);
}

void PongstarBase::releaseAll() {

}

void PongstarBase::resetAll() {

}