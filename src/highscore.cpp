#include "highscore.h"

HighScore::HighScore() {}

HighScore::HighScore(Input* i, DataManager* dm, FontManager* fm) {
	sceneType = sceneNS::HIGH_SCORES;

	input = i;
	dataManager = dm;
	baseFm = fm;
}

HighScore::~HighScore() {}

void HighScore::addHighScore() {
	HighScoreJson hsj;
	HighScoreMap hsm;

	hsj = dataManager->getHighScoreJson();
	hsm = sceneData.modePlayed == sceneNS::GM_CLASSIC ? hsj.classic : hsj.timeAttack;
	hsm[sceneData.newHighScore.score] = sceneData.newHighScore.name;

	if (sceneData.modePlayed == sceneNS::GM_CLASSIC)
		hsj.classic = hsm;
	else
		hsj.timeAttack = hsm;

	dataManager->setHighScoreJson(hsj);
}

void HighScore::initialize(sceneNS::SceneData sd) {
	sceneData = sd;

	titleFm = new FontManager(*baseFm);
	scoreFm = new FontManager(*baseFm);

	scoreFm->setScale(fontNS::SABO_FILLED, 0.4f);

	if (sd.hsDisplayMode != sceneNS::HS_BOTH)
		addHighScore();
	else
		rs = highScoreNS::initialRenderState;
}


void HighScore::update(float frameTime) {
	if (input->wasKeyPressed(ENTER_KEY))
		nextSceneType = sceneNS::MENU;

	if (sceneNS::HS_BOTH) {
		if (input->wasKeyPressed(LEFT_KEY) || input->wasKeyPressed(RIGHT_KEY))
			if (rs == highScoreNS::CLASSIC)
				rs = highScoreNS::TIME_ATK;
			else
				rs = highScoreNS::CLASSIC;
	}
}

void HighScore::renderBottomText(std::string bt) {
	scoreFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		GAME_WIDTH / 2 - scoreFm->getTotalWidth(fontNS::SABO_FILLED, bt) / 2 - fontNS::CENTER_OFFSET,
		highScoreNS::continueStartY,
		bt
		);
}

void HighScore::renderClassicHS() {
	titleFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::nameStartX, highScoreNS::titleStartY, "CLASSIC");
	titleFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::scoreStartX, highScoreNS::titleStartY, "TIME");

	// Display fastest time to get 11 points
	HighScoreMap classicMap = dataManager->getHighScoreJson().classic;
	int index, startHeight, wholeTime, decimalTime;

	// show content:
	for (HighScoreMap::iterator it = classicMap.begin(); it != classicMap.end(); ++it) {
		char nameStr[512], timeStr[512];

		index = std::distance(classicMap.begin(), it);
		startHeight = highScoreNS::contentStartY + index * scoreFm->getHeight(fontNS::SABO_FILLED);
	
		wholeTime = it->first / 1000;			// get first 2 digit for seconds
		decimalTime = it->first % 1000 / 10;	// get first 2 digit after conversion to decimal
		sprintf(nameStr, "%i. %s", index + 1, it->second.c_str());
		sprintf(timeStr, "%i. %02i", wholeTime, decimalTime);
	
		scoreFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::nameStartX, startHeight, nameStr);
		scoreFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::scoreStartX, startHeight, timeStr);

		if (index == 9) 
			break;
	}
}

void HighScore::renderTimeAtkHS() {
	titleFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::nameStartX, highScoreNS::titleStartY, "TIME ATTACK");
	titleFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::scoreStartX, highScoreNS::titleStartY, "SCORE");

	// Display highest score in 60 seconds
	HighScoreMap timeAtkMap = dataManager->getHighScoreJson().timeAttack;
	int index, startHeight;

	for (HighScoreMap::reverse_iterator it = timeAtkMap.rbegin(); it != timeAtkMap.rend(); ++it) {
		char nameStr[512];
		
		index = std::distance(timeAtkMap.rbegin(), it);
		startHeight = highScoreNS::contentStartY + index * scoreFm->getHeight(fontNS::SABO_FILLED);
		
		sprintf(nameStr, "%i. %s", index + 1, it->second.c_str());

		scoreFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::nameStartX, startHeight, nameStr);
		scoreFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::scoreStartX, startHeight, std::to_string(it->first));

		if (index == 9)
			break;
	}
}

void HighScore::renderBothHS() {
	if (rs == highScoreNS::CLASSIC)
		renderClassicHS();
	else
		renderTimeAtkHS();
}

void HighScore::render() {
	switch (sceneData.hsDisplayMode) {
		case sceneNS::HS_CLASSIC: {
			renderClassicHS();
			renderBottomText(highScoreNS::enterToContStr);
		} break;
		case sceneNS::HS_TIME_ATK: {
			renderTimeAtkHS();
			renderBottomText(highScoreNS::enterToContStr);
		} break;
		case sceneNS::HS_BOTH: {
			renderBothHS();
			renderBottomText(highScoreNS::escToBackStr);
		} break;
		default:
			throw(GameError(gameErrorNS::FATAL_ERROR, "Invalid highscore display mode"));
	}
}
