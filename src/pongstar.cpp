#include "pongstar.h"
#include <string>

//=============================================================================
// Constructor
//=============================================================================
Pongstar::Pongstar() {}

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

	dataManager = new DataManager;
	dataManager->initControlData(CONTROLS_JSON);

	fontManager = new FontManager(graphics);
	fontManager->initialize();

	// Textures
	if (!dividerTexture.initialize(graphics, DIVIDER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider texture"));

	if (!paddleTexture.initialize(graphics, PADDLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle texture"));

	if (!ballTexture.initialize(graphics, BALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));

	// Images
	if (!divider.initialize(graphics, 0, 0, 0, &dividerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider"));
	
	this->initializeEntities();

	return;
}

void Pongstar::initializeEntities() {
	ControlsJson controls = dataManager->getControlsJson();

	Paddle *paddle1 = new Paddle(controls.p1);
	Paddle *paddle2 = new Paddle(controls.p2);
	Ball* ball = new Ball();

	if (!paddle1->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, &paddleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	if (!paddle2->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, &paddleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	if (!ball->initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, &ballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	paddle1->setX((float)paddleNS::SIDE_SPACE);
	paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	paddle2->setX(GAME_WIDTH - paddleNS::SIDE_SPACE - paddleNS::WIDTH);
	paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);

	ball->setX(GAME_WIDTH / 2 - ballNS::WIDTH / 2);
	ball->setY(GAME_HEIGHT / 2 - ballNS::HEIGHT / 2);

	entityVector.push_back(paddle1);
	entityVector.push_back(paddle2);
	entityVector.push_back(ball);
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
	// RNG
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomBool(0, 1);

	for (size_t i = 0; i < entityVector.size(); ++i) {
		entityVector[i]->update(frameTime);

		if (entityVector[i]->getEntityType() == entityNS::BALL) {
			VECTOR2 ballVelocity = entityVector[i]->getVelocity();

			// If ball is stationary
			if (ballVelocity.x == 0 && ballVelocity.y == 0) {
				if (input->wasKeyPressed(SPACE_KEY)) {
					// Randomize initial ball direction (left or right)
					float startingVelocity = (randomBool(rng) == 1) ? ballNS::VELOCITY : -ballNS::VELOCITY;
					entityVector[i]->setVelocity(VECTOR2(startingVelocity, 0));
				}
			}
		}
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
				switch (entityVector[i]->getEntityType()) {
				case entityNS::BALL:
					if (entityVector[i]->collidesWith(*entityVector[j], collisionVector)) {
						entityVector[i]->paddleBounce(collisionVector, *entityVector[j], ballNS::VELOCITY);
					}
					break;
				}
			}
		}
	}
}

//==========================================================i]===================
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
		GAME_WIDTH / 2 - fontManager->getTotalWidth(fontNS::SABO_FILLED, "60") /2 - fontNS::CENTER_OFFSET,
		HUD_Y_POS,
		"60"
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

	fontManager->resetAll();

	Game::resetAll();
	return;
}
