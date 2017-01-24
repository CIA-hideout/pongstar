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

	effectManager = new EffectManager();

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
	// RNG
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomBumperX(0, 240);
	std::uniform_int_distribution<int> randomBumperY(0, 640);

	ControlsJson controls = dataManager->getControlsJson();

	Paddle* paddle1 = new Paddle(controls.p1);
	Paddle* paddle2 = new Paddle(controls.p2);
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

	
	bumper->setX(randomBumperX(rng) + GAME_WIDTH / 4);
	bumper->setY(randomBumperY(rng));

	entityVector.push_back(paddle1);
	entityVector.push_back(paddle2);
	entityVector.push_back(ball);
	entityVector.push_back(bumper);

	// randomly generate basic set of pickups
	Pickup* pickup = pickupManager->randomPickup(this);

<<<<<<< HEAD
	pickup->setX(GAME_WIDTH / 4);
	pickup->setY(GAME_HEIGHT / 2 - (pickupNS::HEIGHT * pickupNS::SCALE) / 2);

	//entityVector.push_back(pickup);
=======
	entityVector.push_back(pickup);
>>>>>>> Make pickup spawn at a random location along the middle
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
	effectManager->update(frameTime);

	for (size_t i = 0; i < entityVector.size(); ++i) {
		entityVector[i]->update(frameTime);
		entityVector[i]->runEffects(*effectManager);

		if (!entityVector[i]->getActive()) {
			deleteEntityQueue.push(i);
		}
	}

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
				entityVector[i]->collidesWith(*entityVector[j], collisionVector, *effectManager);
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

	fontManager->print(
		fontNS::SABO_FILLED,
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, "60") / 2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		std::to_string(TIME_PER_GAME - elapsedTime)
	);

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
