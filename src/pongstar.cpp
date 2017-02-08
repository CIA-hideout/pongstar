#include "pongstar.h"

const char* textureToString(textureNS::TEXTURE t) {
	switch (t) {
		case textureNS::BALL:		return "Ball";
		case textureNS::PADDLE:		return "Paddle";
		case textureNS::DIVIDER:	return "Divider";
		case textureNS::BUMPER:		return "Bumper";
		case textureNS::BORDER:		return "Border";
		case textureNS::PICKUPS:	return "Pickups";
		default:					return "Unable to find string conversion for texture";
	}
}

//=============================================================================
// Constructor
//=============================================================================
Pongstar::Pongstar() {
	gameStack = new std::stack<Scene*>;
	muted = false;
}

//=============================================================================
// Destructor
//=============================================================================
Pongstar::~Pongstar() {
	Pongstar::releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Pongstar::initialize(HWND hwnd) {
	Game::initialize(hwnd); // throws GameError

	dataManager = new DataManager();
	dataManager->initControlData();
	dataManager->initHighScoreData();

	fontManager = new FontManager(graphics);
	fontManager->initialize();

	TextureManager* tm;
	textureNS::TEXTURE texture;

	for (size_t i = 0; i < textureNS::initTextureVec.size(); i++) {
		char textureLocation[1024], errorMsg[1024];
		tm = new TextureManager();
		texture = textureNS::initTextureVec[i];

		sprintf(textureLocation, "%s%s.png", textureNS::TEXTURE_DIRECTORY, textureToString(texture));
		sprintf(errorMsg, "Error initializing %s texture", textureToString(texture));

		if (!tm->initialize(graphics, textureLocation))
			throw(GameError(gameErrorNS::FATAL_ERROR, errorMsg));

		tmMap.insert(std::pair<textureNS::TEXTURE, TextureManager*>(texture, tm));
	}

	sceneNS::SceneData sd = sceneNS::SceneData();
	sd.playMenuCue = true;
	sd.playGameCue = false;

	Menu* menu = new Menu(audio ,input, fontManager);
	menu->initialize(sd);
	gameStack->push(menu);
}

//=============================================================================
// Update all game items
//=============================================================================
void Pongstar::update() {
	if (muted)
		audio->muteCategory("default");
	else
		audio->unmuteCategory("default");

	gameStack->top()->update(frameTime);

	sceneNS::TYPE currSceneType = gameStack->top()->getSceneType();
	sceneNS::SceneData currSceneData = gameStack->top()->getSceneData();

	bool escToMenu = gameStack->top()->getSceneData().escToMenu;

	bool allowEsc =
		currSceneType == sceneNS::INSTRUCTIONS ||
		currSceneType == sceneNS::CLASSIC ||
		currSceneType == sceneNS::TIME_ATK ||
		currSceneType == sceneNS::CREDITS ||
		currSceneType == sceneNS::HIGH_SCORES;

	if (input->wasKeyPressed(ESC_KEY) && allowEsc && gameStack->size() > 1 && !escToMenu) {
		gameStack->pop();
		audio->playCue(ESC_CUE);
		gameStack->top()->initialize(currSceneData);
	}

	if (input->wasKeyPressed(ESC_KEY) && allowEsc && escToMenu) {
		gameStack->top()->setNextSceneType(sceneNS::MENU);
		audio->playCue(ESC_CUE);
	}

	if (gameStack->top()->getNextSceneType() != sceneNS::NONE) {
		sceneNS::TYPE nextSceneType = gameStack->top()->getNextSceneType();
		sceneNS::SceneData sd = gameStack->top()->getSceneData();
		Scene* nextScene = nullptr;

		switch (nextSceneType) {
			case sceneNS::INSTRUCTIONS: {
				nextScene = new Instructions(this, audio, fontManager);
			} break;
			case sceneNS::CLASSIC: {
				nextScene = new Classic(this, audio, dataManager, fontManager, tmMap);
			} break;
			case sceneNS::TIME_ATK: {
				nextScene = new TimeAttack(this, audio, dataManager, fontManager, tmMap);
			} break;
			case sceneNS::HIGH_SCORES: {
				nextScene = new HighScore(audio, input, dataManager, fontManager);
			} break;
			case sceneNS::CREDITS: {
				nextScene = new Credits(input, fontManager);
			} break;
			case sceneNS::GAMEOVER: {
				nextScene = new Gameover(this, audio, fontManager);
			} break;

			case sceneNS::MENU:
			default:
				break;
		}

		if (nextSceneType == sceneNS::MENU) {
			// Pop everything to base layer
			while (gameStack->size() > 1) {
				gameStack->pop();
			}
		} else {
			gameStack->top()->clearNextSceneType();
			nextScene->initialize(sd);
			gameStack->push(nextScene);
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

	dataManager->saveHighScore();
	fontManager->releaseAll();

	Game::releaseAll();
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
}
