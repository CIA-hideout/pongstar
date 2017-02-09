#include "pongstarBase.h"

PongstarBase::PongstarBase(Game* g, Audio* a, DataManager* dm, FontManager* fm, TextureManagerMap t) {
	game = g;
	audio = a;
	dataManager = dm;
	fontManager = fm;
	tmMap = t;
}

PongstarBase::~PongstarBase() {}

void PongstarBase::initialize(sceneNS::SceneData sd) {
	sceneData = sd;

	if (sceneData.playGameCue) {
		audio->stopCue(MENU_CUE);
		audio->playCue(GAME_CUE);
	}

	sceneData.playMenuCue = true;
	sceneData.playGameCue = false;

	pickupDelayTimers = new IntFloatMap();
	entityManager = new EntityManager(game, &tmMap, pickupDelayTimers);
	pickupManager = new PickupManager(game, tmMap[textureNS::PICKUPS], entityManager, pickupDelayTimers);
	messageManager = new MessageManager(pickupManager, entityManager);

	if (!divider.initialize(game->getGraphics(), 0, 0, 0, tmMap[textureNS::DIVIDER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing divider"));

	if (!border.initialize(game->getGraphics(), 0, 0, 0, tmMap[textureNS::BORDER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing border"));

	initializeEntities();
}

void PongstarBase::initializeEntities() {
	ControlsJson controls = dataManager->getControlsJson();

	Paddle* paddle1 = new Paddle(game->getGraphics(), controls.p1, paddleNS::LEFT);
	Paddle* paddle2 = new Paddle(game->getGraphics(), controls.p2, paddleNS::RIGHT);
	Bumper* bumper = new Bumper();

	if (!paddle1->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[textureNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle1"));

	if (!paddle2->initialize(game, paddleNS::WIDTH, paddleNS::HEIGHT, paddleNS::NCOLS, tmMap[textureNS::PADDLE]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle2"));

	if (!bumper->initialize(game, bumperNS::WIDTH, bumperNS::HEIGHT, bumperNS::NCOLS, tmMap[textureNS::BUMPER]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bumper"));

	paddle1->setX((float)paddleNS::SIDE_SPACE);
	paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	paddle2->setX(GAME_WIDTH - paddleNS::SIDE_SPACE - paddleNS::WIDTH);
	paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);

	entityManager->addEntity(paddle1);
	entityManager->addEntity(paddle2);
	entityManager->addEntity(bumper);

	Ball* ball = entityManager->createBall();
	ball->setX(GAME_WIDTH / 2 - ballNS::WIDTH / 2);
	ball->setY(GAME_HEIGHT / 2 - ballNS::HEIGHT / 2);

	// For pickups testing
	//pickupManager->testPickup(effectNS::MULTIPLY);
	//pickupManager->massSpawnPickups(1);
	pickupManager->massSpawnContrastPickups();
}

void PongstarBase::update(float frameTime) {
	Input* input = game->getInput();
	std::map<int, Entity*>* eMap = entityManager->getEntityMap();
	Entity* entity;

	for (auto& x : *eMap) {
		entity = x.second;
		entity->update(frameTime);

		if (!entity->getActive())
			deleteEntityQueue.push(entity->getId());

		while (entity->getMessageQueue().size() > 0) {
			messageManager->push(entity->getMessageQueue().front());
			entity->popMsg();
		}
	}

	messageManager->resolve();
	messageManager->update(frameTime);

	while (deleteEntityQueue.size() > 0) {
		int idToRemove = deleteEntityQueue.front();
		entityManager->deleteEntity(idToRemove);
		deleteEntityQueue.pop();
	}

	if (input->wasKeyPressed(SPACE_KEY) && !gameStarted) {
		startTime = steady_clock::now();
		gameStarted = true;
		entityManager->getBalls()[0]->randomStartBall();
	}

	if (gameStarted) {
		steady_clock::time_point presentTime = steady_clock::now();
		elapsedTime = duration_cast<milliseconds>(presentTime - startTime).count();
	}

	for (auto& x : *pickupDelayTimers) {
		if (x.second > 0)
			x.second -= frameTime;
	}
}

void PongstarBase::ai() {}

void PongstarBase::collisions() {
	VECTOR2 collisionVector;

	for (auto& x : *entityManager->getEntityMap()) {
		for (auto& y : *entityManager->getEntityMap()) {
			if (x.second->getId() != y.second->getId())
				x.second->collidesWith(*y.second, collisionVector);
		}
	}
}

void PongstarBase::render() {
	divider.draw();

	for (auto& x : *entityManager->getEntityMap()) {
		x.second->draw();
	}

	border.draw();

	std::string leftPaddleScore = std::to_string(entityManager->getPaddle(paddleNS::LEFT)->getScore());
	std::string rightPaddleScore = std::to_string(entityManager->getPaddle(paddleNS::RIGHT)->getScore());

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
