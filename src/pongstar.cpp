#include "pongstar.h"
#include <string>

//=============================================================================
// Constructor
//=============================================================================
Pongstar::Pongstar() {
	elapsedTime = 0;
	gameStarted = false;
}

//=============================================================================
// Destructor
//=============================================================================
Pongstar::~Pongstar() {
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Pongstar::initialize(HWND hwnd) {
	Game::initialize(hwnd); // throws GameError

	dataManager = new DataManager();
	dataManager->initControlData(CONTROLS_JSON);

	fontManager = new FontManager(graphics);
	fontManager->initialize();

	pickupManager = new PickupManager(graphics);

	messageManager = new MessageManager(&entityVector);

	// Textures
	if (!dividerTexture.initialize(graphics, DIVIDER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider texture"));

	if (!paddleTexture.initialize(graphics, PADDLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle texture"));

	if (!ballTexture.initialize(graphics, BALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));

	if (!bumperTexture.initialize(graphics, BUMPER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bumper texture"));

	// Images
	if (!divider.initialize(graphics, 0, 0, 0, &dividerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider"));

	this->initializeEntities();

	return;
}

void Pongstar::initializeEntities() {
	ControlsJson controls = dataManager->getControlsJson();

	Paddle* paddle1 = new Paddle(controls.p1, paddleNS::LEFT);
	Paddle* paddle2 = new Paddle(controls.p2, paddleNS::RIGHT);
	Ball* ball = new Ball();
	Bumper* bumper = new Bumper();

	if (!paddle1->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, &paddleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	if (!paddle2->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, &paddleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	if (!ball->initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, &ballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	if (!bumper->initialize(this, bumperNS::WIDTH, bumperNS::HEIGHT, bumperNS::NCOLS, &bumperTexture))
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

	// randomly generate basic set of pickups
	//Pickup* pickup = pickupManager->randomPickup(this);
	Pickup* pickup = pickupManager->createPickup(this, effectNS::ENLARGE);

	pickup->setX(GAME_WIDTH / 4);
	pickup->setY(GAME_HEIGHT / 2 - (pickupNS::HEIGHT * pickupNS::SCALE) / 2);
	

	entityVector.push_back(pickup);
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
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

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Pongstar::ai() {}

//=============================================================================
// Handle collisions
//=============================================================================
void Pongstar::collisions() {
	VECTOR2 collisionVector;

	for (size_t i = 0; i < entityVector.size(); ++i) {
		for (size_t j = 0; j < entityVector.size(); ++j) {
			if (entityVector[i]->getId() != entityVector[j]->getId()) {
				entityVector[i]->collidesWith(*entityVector[j], collisionVector);
			}
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Pongstar::render() {
	graphics->spriteBegin();                // begin drawing sprites

	divider.draw();

	for (size_t i = 0; i < entityVector.size(); ++i) {
		entityVector[i]->draw();
	}

	std::string timeLeft = std::to_string(TIME_PER_GAME - elapsedTime);
	std::string leftPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::LEFT)->getScore());
	std::string rightPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::RIGHT)->getScore());

	fontManager->print(
		fontNS::SABO_FILLED,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, timeLeft) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		timeLeft
	);

	fontManager->print(
		fontNS::SABO_FILLED,
		GAME_WIDTH / 4 - fontManager->getTotalWidth(fontNS::SABO_FILLED, leftPaddleScore) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		leftPaddleScore
	);

	fontManager->print(
		fontNS::SABO_FILLED,
		GAME_WIDTH / 4 * 3 - fontManager->getTotalWidth(fontNS::SABO_FILLED, rightPaddleScore) / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		rightPaddleScore
	);

	//printf("P1: %i   P2: %i\n", messageManager->getPaddle(paddleNS::LEFT)->getScore(), messageManager->getPaddle(paddleNS::RIGHT)->getScore());

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Pongstar::releaseAll() {
	dividerTexture.onLostDevice();
	paddleTexture.onLostDevice();
	ballTexture.onLostDevice();
	bumperTexture.onLostDevice();

	fontManager->releaseAll();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Pongstar::resetAll() {
	dividerTexture.onResetDevice();
	paddleTexture.onResetDevice();
	ballTexture.onResetDevice();
	bumperTexture.onResetDevice();

	fontManager->resetAll();

	Game::resetAll();
	return;
}
