#include "highscore.h"

HighScore::HighScore() {}

HighScore::HighScore(Audio* a, Input* i, DataManager* dm, FontManager* fm) {
	sceneType = sceneNS::HIGH_SCORES;
	audio = a;
	input = i;
	baseFm = fm;
	dataManager = dm;
}

HighScore::~HighScore() {}

void HighScore::addHighScore() {
	HighScoreJson hsJson;
	HighScoreMap hsMap;

	hsJson = dataManager->getHighScoreJson();
	int score;

	if (sceneData.gameMode == sceneNS::GM_CLASSIC) {
		hsMap = hsJson.classic;
		score = sceneData.scores.time;
	} else {
		hsMap = hsJson.timeAttack;
		score = (sceneData.scores.p1Score > sceneData.scores.p2Score) ? sceneData.scores.p1Score : sceneData.scores.p2Score;
	}

	hsMap.insert(std::pair<int, std::string>(score, sceneData.scores.name)); 
	
	if (sceneData.gameMode == sceneNS::GM_CLASSIC)
		hsJson.classic = hsMap;
	else
		hsJson.timeAttack = hsMap;

	dataManager->setHighScoreJson(hsJson);
}

void HighScore::initialize(sceneNS::SceneData sd) {
	sceneData = sd;

	if (sceneData.playMenuCue) {
		audio->stopCue(GAME_CUE);
		audio->playCue(MENU_CUE);
	}

	sceneData.playMenuCue = false;
	sceneData.playGameCue = false;
	sceneData.escToMenu = true;

	blink = true;

	largeFm = new FontManager(*baseFm);
	smallFm = new FontManager(*baseFm);

	float scale = highScoreNS::LARGE_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	largeFm->setScale(fontNS::SABO_FILLED, scale);
	largeFm->setScale(fontNS::SABO, scale);
	
	scale = highScoreNS::SMALL_FONT_SIZE / fontNS::DEFAULT_FONT_SIZE;
	smallFm->setScale(fontNS::SABO_FILLED, scale);
	smallFm->setScale(fontNS::SABO, scale);

	// Add score to json
	if (sd.scores.name != "")
		addHighScore();
}

void HighScore::update(float frameTime) {
	if (input->wasKeyPressed(ENTER_KEY)) {
		nextSceneType = sceneNS::MENU;
		audio->playCue(ESC_CUE);
	}

	if (input->wasKeyPressed(UP_KEY) || input->wasKeyPressed(DOWN_KEY)) {
		audio->playCue(NAVIGATION_CUE);
		if (sceneData.gameMode == sceneNS::GM_TIME_ATK)
			sceneData.gameMode = sceneNS::GM_CLASSIC;
		else
			sceneData.gameMode = sceneNS::GM_TIME_ATK;
	}

	if (blinkTimer < highScoreNS::BLINK_INTERVAL) {
		blinkTimer += frameTime;
	}
	else {
		blink = !blink;
		blinkTimer = 0.0;
	}
}

// Display fastest time to get 11 points
void HighScore::renderClassicHS() {
	HighScoreMap classicMap = dataManager->getHighScoreJson().classic;
	int index, startHeight, wholeTime, decimalTime, timeXpos;

	int height = largeFm->getHeight(fontNS::SABO_FILLED) + highScoreNS::RANK_VERT_GAP;

	// show content:
	for (HighScoreMap::iterator it = classicMap.begin(); it != classicMap.end(); ++it) {
		char rankStr[512], nameStr[512], timeStr[512];

		index = std::distance(classicMap.begin(), it);
		startHeight = highScoreNS::OVERALL_Y_POS + index * height;
	
		wholeTime = it->first / 1000;			// get first 2 digit for seconds
		decimalTime = it->first % 1000 / 10;	// get first 2 digit after conversion to decimal
		sprintf(rankStr, "%i", index + 1);
		sprintf(nameStr, "%s", it->second.c_str());
		sprintf(timeStr, "%i.%02i", wholeTime, decimalTime);

		timeXpos = highScoreNS::SCORE_RIGHT_X_POS - largeFm->getTotalWidth(fontNS::SABO_FILLED, timeStr);
	
		largeFm->print(fontNS::SABO_FILLED, fontNS::GREY, highScoreNS::RANK_X_POS, startHeight, rankStr);
		largeFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::NAME_X_POS, startHeight, nameStr);
		largeFm->print(fontNS::SABO_FILLED, fontNS::WHITE, timeXpos, startHeight, timeStr);

		if (index == 9) break;
	}
}

// Display highest score in 60 seconds
void HighScore::renderTimeAtkHS() {
	HighScoreMap timeAtkMap = dataManager->getHighScoreJson().timeAttack;
	int index, startHeight, scoreXpos;

	int height = largeFm->getHeight(fontNS::SABO_FILLED) + highScoreNS::RANK_VERT_GAP;

	for (HighScoreMap::reverse_iterator it = timeAtkMap.rbegin(); it != timeAtkMap.rend(); ++it) {
		char rankStr[512], nameStr[512];
		
		index = std::distance(timeAtkMap.rbegin(), it);
		startHeight = highScoreNS::OVERALL_Y_POS + index * height;
		
		sprintf(rankStr, "%i", index + 1);
		sprintf(nameStr, "%s", it->second.c_str());

		scoreXpos = highScoreNS::SCORE_RIGHT_X_POS - largeFm->getTotalWidth(fontNS::SABO_FILLED, std::to_string(it->first));

		largeFm->print(fontNS::SABO_FILLED, fontNS::GREY, highScoreNS::RANK_X_POS, startHeight, rankStr);
		largeFm->print(fontNS::SABO_FILLED, fontNS::WHITE, highScoreNS::NAME_X_POS, startHeight, nameStr);
		largeFm->print(fontNS::SABO_FILLED, fontNS::WHITE, scoreXpos, startHeight, std::to_string(it->first));

		if (index == 9) break;
	}
}

void HighScore::render() {
	// Render 'HIGHSCORES' text
	smallFm->setKerning(fontNS::SABO_FILLED, 10);
	smallFm->setKerning(fontNS::SABO, 10);

	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::RED,
		highScoreNS::SIDEBAR_X_POS,
		highScoreNS::OVERALL_Y_POS,
		"HIGH"
	);

	smallFm->print(
		fontNS::SABO,
		fontNS::RED,
		highScoreNS::SIDEBAR_X_POS + smallFm->getTotalWidth(fontNS::SABO_FILLED, "HIGH"),
		highScoreNS::OVERALL_Y_POS,
		"SCORES"
	);

	// Render 'CLASSIC' & 'TIME ATTACK' text
	largeFm->setKerning(fontNS::SABO_FILLED, 0);
	largeFm->setKerning(fontNS::SABO, 0);

	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		highScoreNS::SIDEBAR_X_POS,
		highScoreNS::CLASSIC_Y_POS,
		"CLASSIC"
	);

	largeFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		highScoreNS::SIDEBAR_X_POS,
		highScoreNS::TIME_ATK_Y_POS,
		"TIME ATTACK"
	);

	// Render marker indicating game mode
	int markerWidth = largeFm->getTotalWidth(fontNS::SABO, "-");
	int markerYpos = (sceneData.gameMode == sceneNS::GM_TIME_ATK) ? highScoreNS::TIME_ATK_Y_POS : highScoreNS::CLASSIC_Y_POS;

	largeFm->print(
		fontNS::SABO,
		fontNS::ORANGE,
		highScoreNS::SIDEBAR_X_POS - markerWidth - highScoreNS::BLINKER_GAP,
		markerYpos - 6,
		"-"
	);

	largeFm->print(
		fontNS::SABO,
		fontNS::BLUE,
		highScoreNS::SIDEBAR_X_POS - markerWidth - highScoreNS::BLINKER_GAP,
		markerYpos + 6,
		"-"
	);

	// Render 'PRESS ESC' text and blinkers
	smallFm->setKerning(fontNS::SABO_FILLED, 0);
	smallFm->setKerning(fontNS::SABO, 0);

	int escWidth = smallFm->getTotalWidth(fontNS::SABO_FILLED, "PRESS ESC");

	if (blink) {
		smallFm->print(
			fontNS::SABO,
			fontNS::ORANGE,
			highScoreNS::ESC_X_POS - smallFm->getTotalWidth(fontNS::SABO, "-") - highScoreNS::BLINKER_GAP,
			highScoreNS::ESC_Y_POS,
			"-"
		);

		smallFm->print(
			fontNS::SABO,
			fontNS::BLUE,
			highScoreNS::ESC_X_POS + escWidth + highScoreNS::BLINKER_GAP,
			highScoreNS::ESC_Y_POS,
			"-"
		);
	}

	smallFm->print(
		fontNS::SABO_FILLED,
		fontNS::WHITE,
		highScoreNS::ESC_X_POS,
		highScoreNS::ESC_Y_POS,
		"PRESS ESC"
	);

	if (sceneData.gameMode == sceneNS::GM_TIME_ATK)
		renderTimeAtkHS();
	else
		renderClassicHS();
}
