#include "pongstar.h"
#include <string>

const char* textureToString(pongstarNS::TEXTURE t) {
	switch (t) {
	case pongstarNS::BALL:			return "Ball";
	case pongstarNS::PADDLE:		return "Paddle";
	case pongstarNS::DIVIDER:		return "Divider";
	case pongstarNS::BUMPER:		return "Bumper";
	}
}

//=============================================================================
// Constructor
//=============================================================================
Pongstar::Pongstar() {
	elapsedTime = 0;
	gameStarted = false;
	gameState = GAME_STATE::GAME;
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

	menu = new Menu();
	menu->initialize(input, fontManager);

	TextureManager* tm;
	pongstarNS::TEXTURE texture;

	for (size_t i = 0; i < pongstarNS::initTextureVec.size(); i++) {
		char textureLocation[1024], errorMsg[1024];
		tm = new TextureManager();
		texture = pongstarNS::initTextureVec[i];

		sprintf(textureLocation, "%s%s.png", pongstarNS::TEXTURE_DIRECTORY, textureToString(texture));
		sprintf(errorMsg, "Erorr initializing %s texture", textureToString(texture));

		if (!tm->initialize(graphics, textureLocation))
			throw(GameError(gameErrorNS::FATAL_ERROR, errorMsg));

		tmMap.insert(std::pair<pongstarNS::TEXTURE, TextureManager*>(texture, tm));
	}

	// Images
	if (!divider.initialize(graphics, 0, 0, 0, tmMap[pongstarNS::DIVIDER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider"));

	ps = new PongstarBase(dataManager, fontManager, messageManager, tmMap, this, input);
	ps->initialize(divider);

	//this->initializeEntities();

	return;
}

void Pongstar::initializeEntities() {
	//ControlsJson controls = dataManager->getControlsJson();

	//Paddle* paddle1 = new Paddle(controls.p1, paddleNS::LEFT);
	//Paddle* paddle2 = new Paddle(controls.p2, paddleNS::RIGHT);
	//Ball* ball = new Ball();
	//Bumper* bumper = new Bumper();

	//if (!paddle1->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	//if (!paddle2->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[pongstarNS::PADDLE]))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	//if (!ball->initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::NCOLS, tmMap[pongstarNS::BALL]))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	//if (!bumper->initialize(this, bumperNS::WIDTH, bumperNS::HEIGHT, bumperNS::NCOLS, tmMap[pongstarNS::BUMPER]))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bumper"));

	//paddle1->setX((float)paddleNS::SIDE_SPACE);
	//paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	//paddle2->setX(GAME_WIDTH - paddleNS::SIDE_SPACE - paddleNS::WIDTH);
	//paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);

	//ball->setX(GAME_WIDTH / 2 - ballNS::WIDTH / 2);
	//ball->setY(GAME_HEIGHT / 2 - ballNS::HEIGHT / 2);

	//entityVector.push_back(paddle1);
	//entityVector.push_back(paddle2);
	//entityVector.push_back(ball);
	//entityVector.push_back(bumper);
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
	switch (gameState) {
	case GAME_STATE::MENU: {
		menu->update(frameTime);
	} break;
	case GAME_STATE::GAME: {
		ps->update(frameTime);
		//for (size_t i = 0; i < entityVector.size(); ++i) {
		//	entityVector[i]->update(frameTime);

		//	if (!entityVector[i]->getActive()) {
		//		deleteEntityQueue.push(i);
		//	}

		//	if (entityVector[i]->getMessage() != NULL) {
		//		messageManager->push(entityVector[i]->getMessage());
		//		entityVector[i]->setMessage(NULL);
		//	}
		//}

		//while (deleteEntityQueue.size() > 0) {
		//	int indexToRemove = deleteEntityQueue.front();
		//	entityVector.erase(entityVector.begin() + indexToRemove);
		//	deleteEntityQueue.pop();
		//}

		//messageManager->resolve();

		//if (input->wasKeyPressed(SPACE_KEY) && !gameStarted) {
		//	startTime = steady_clock::now();
		//	gameStarted = true;
		//}

		//if (gameStarted) {
		//	steady_clock::time_point presentTime = steady_clock::now();
		//	elapsedTime = duration_cast<seconds>(presentTime - startTime).count();
		//}
	} break;
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
	switch (gameState) {
	case GAME_STATE::MENU: {

	} break;
	case GAME_STATE::GAME: {
		ps->collisions();
		//VECTOR2 collisionVector;

		//for (size_t i = 0; i < entityVector.size(); ++i) {
		//	for (size_t j = 0; j < entityVector.size(); ++j) {
		//		if (entityVector[i]->getId() != entityVector[j]->getId()) {
		//			entityVector[i]->collidesWith(*entityVector[j], collisionVector);
		//		}
		//	}
		//}
	} break;
	}

}

//=============================================================================
// Render game items
//=============================================================================
void Pongstar::render() {
	graphics->spriteBegin();                // begin drawing sprites
	switch (gameState) {
	case GAME_STATE::MENU: {
		menu->render();
	} break;
	case GAME_STATE::GAME: {
		ps->render();
	/*	divider.draw();

		for (size_t i = 0; i < entityVector.size(); ++i) {
			entityVector[i]->draw();
		}

		border.draw();

		std::string timeLeft = std::to_string(TIME_PER_GAME - elapsedTime);
		std::string leftPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::LEFT)->getScore());
		std::string rightPaddleScore = std::to_string(messageManager->getPaddle(paddleNS::RIGHT)->getScore());

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
		);*/
	} break;

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Pongstar::releaseAll() {
	for (auto &tm : tmMap) {
		tm.second->onLostDevice();
	}

	fontManager->releaseAll();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Pongstar::resetAll() {
	for (auto &tm : tmMap) {
		tm.second->onResetDevice();
	}

	fontManager->resetAll();

	Game::resetAll();
	return;
}
