#include "pongstarBase.h"

PongstarBase::PongstarBase(Game* g, DataManager* dm, FontManager* fm, TextureManagerMap t) {
	game = g;
	dataManager = dm;
	fontManager = fm;
	tmMap = t;
}

PongstarBase::~PongstarBase() {}

void PongstarBase::initialize() {
	ballManager = new BallManager(game, tmMap[pongstarNS::BALL], &entityVector);
	pickupManager = new PickupManager(game, tmMap[pongstarNS::PICKUPS], &entityVector);
	messageManager = new MessageManager(pickupManager, ballManager, &entityVector);

	if (!divider.initialize(game->getGraphics(), 0, 0, 0, tmMap[pongstarNS::DIVIDER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider"));

	if (!border.initialize(game->getGraphics(), 0, 0, 0, tmMap[pongstarNS::BORDER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing border"));

	initializeEntities();
}

void PongstarBase::initializeEntities() {
	ControlsJson controls = dataManager->getControlsJson();

	Paddle* paddle1 = new Paddle(controls.p1, paddleNS::LEFT);
	Paddle* paddle2 = new Paddle(controls.p2, paddleNS::RIGHT);
	Bumper* bumper = new Bumper();

	if (!paddle1->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	if (!paddle2->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	if (!bumper->initialize(game, bumperNS::WIDTH, bumperNS::HEIGHT, bumperNS::NCOLS, tmMap[pongstarNS::BUMPER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bumper"));

	paddle1->setX((float)paddleNS::SIDE_SPACE);
	paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	paddle2->setX(GAME_WIDTH - paddleNS::SIDE_SPACE - paddleNS::WIDTH);
	paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);

	entityVector.push_back(paddle1);
	entityVector.push_back(paddle2);
	entityVector.push_back(bumper);

	Ball* ball = ballManager->createBall();
	ball->setX(GAME_WIDTH / 2 - ballNS::WIDTH / 2);
	ball->setY(GAME_HEIGHT / 2 - ballNS::HEIGHT / 2);

	// For pickups testing
	pickupManager->createPickup(effectNS::MULTIPLY);
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

	messageManager->resolve();

	while (deleteEntityQueue.size() > 0) {
		int indexToRemove = deleteEntityQueue.front();
		entityVector.erase(entityVector.begin() + indexToRemove);
		deleteEntityQueue.pop();
	}

	if (input->wasKeyPressed(SPACE_KEY) && !gameStarted) {
		startTime = steady_clock::now();
		gameStarted = true;
	}

	if (gameStarted) {
		steady_clock::time_point presentTime = steady_clock::now();
		elapsedTime = duration_cast<seconds>(presentTime - startTime).count();
	}
}

void PongstarBase::ai() {}

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

	border.draw();

	std::string leftPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::LEFT)->getScore());
	std::string rightPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::RIGHT)->getScore());

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

void PongstarBase::releaseAll() {}

void PongstarBase::resetAll() {}
