#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include <map>
#include <string>
#include <iterator>

#include "gameError.h"
#include "input.h"
#include "fontManager.h"
#include "scene.h"

namespace highScoreNS {
	const int nameStartX = 300;
	const int scoreStartX = 750;
	const int titleStartY = 20;

	const int contentStartY = 100;
	const int continueStartY = 640;
	
	const std::string enterToContStr = "PRESS ENTER TO CONTINUE";
	const std::string escToBackStr = "PRESS ESC TO GO BACK";

	// manage which highscore is showing if displayMode is set to both
	enum RENDER_STATE { CLASSIC, TIME_ATK };
	const RENDER_STATE initialRenderState = CLASSIC;
}

class HighScore : public Scene {
private:
	Input* input;
	DataManager* dataManager;
	FontManager* baseFm;

	FontManager* titleFm;
	FontManager* scoreFm;

	highScoreNS::RENDER_STATE rs;	

	void addHighScore();
	void renderBottomText(std::string bt);
	void renderClassicHS();
	void renderTimeAtkHS();
	void renderBothHS();
public:
	HighScore();
	HighScore(Input* i, DataManager* dm, FontManager* fm);
	~HighScore();

	// Interface
	void initialize(sceneNS::SceneData sd);
	void update(float frameTime);
	void ai() {};
	void collisions() {};
	void render();

	void releaseAll() {};
	void resetAll() {};
};

#endif