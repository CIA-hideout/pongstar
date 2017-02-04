#include "pongstar.h"
#include <string>

const char* textureToString(pongstarNS::TEXTURE t) {
	switch (t) {
	case pongstarNS::BALL:			return "Ball";
	case pongstarNS::PADDLE:		return "Paddle";
	case pongstarNS::DIVIDER:		return "Divider";
	case pongstarNS::BUMPER:		return "Bumper";
	case pongstarNS::BORDER:		return "Border";
	case pongstarNS::PICKUPS:		return "Pickups";
	default:						return "Unable to find string conversion for texture";
	}
}

//=============================================================================
// Constructor
//=============================================================================
Pongstar::Pongstar() {
	gameStack = new std::stack<Scene*>;
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

	TextureManager* tm;
	pongstarNS::TEXTURE texture;

	for (size_t i = 0; i < pongstarNS::initTextureVec.size(); i++) {
		char textureLocation[1024], errorMsg[1024];
		tm = new TextureManager();
		texture = pongstarNS::initTextureVec[i];

		sprintf(textureLocation, "%s%s.png", pongstarNS::TEXTURE_DIRECTORY, textureToString(texture));
		sprintf(errorMsg, "Error initializing %s texture", textureToString(texture));

		if (!tm->initialize(graphics, textureLocation))
			throw(GameError(gameErrorNS::FATAL_ERROR, errorMsg));

		tmMap.insert(std::pair<pongstarNS::TEXTURE, TextureManager*>(texture, tm));
	}

	Menu* menu = new Menu(input, fontManager);
	menu->initialize();
	gameStack->push(menu);

	//PongstarBase* ps = new PongstarBase(this, dataManager, fontManager, tmMap);
	//ps->initialize();
	//gameStack->push(ps);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
	gameStack->top()->update(frameTime);

	if (input->wasKeyPressed(ESC_KEY) && gameStack->size() > 1)
		gameStack->pop();

	if (gameStack->top()->getNextSceneType() != NULL) {
		sceneNS::TYPE nextSceneType = *gameStack->top()->getNextSceneType();
		gameStack->top()->clearNextSceneType();
		Scene* nextScene;

		switch (nextSceneType) {
			case sceneNS::CLASSIC: {
				nextScene = new PongstarBase(this, dataManager, fontManager, tmMap);
				nextScene->initialize();
			} break;
		}

		gameStack->push(nextScene);
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
	gameStack->top()->collisions();
}

//=============================================================================
// Render game items
//=============================================================================
void Pongstar::render() {
	graphics->spriteBegin();                // begin drawing sprites
	gameStack->top()->render();
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
