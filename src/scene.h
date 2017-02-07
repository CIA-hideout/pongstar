// Interface class for implementing scenes

#ifndef _SCENE_H
#define _SCENE_H

#include <string>

namespace sceneNS {
	enum TYPE {
		MENU, INSTRUCTIONS, CLASSIC, TIME_ATK, HIGH_SCORES, CREDITS, VICTORY, NONE
	};

	enum GAME_MODE {
		GM_CLASSIC, GM_TIME_ATK
	};

	enum WINNER {
		W_LEFT, W_RIGHT, W_DRAW
	};

	struct NewHighScore {
		int score;
		std::string name;
	};

	struct SceneData {	// data to be passed down scene to scene
		WINNER winner;
		GAME_MODE gameMode;
		NewHighScore newHighScore;
		bool escToMenu = false;
	};
}

class Scene {
protected:
	sceneNS::TYPE sceneType = sceneNS::NONE;
	sceneNS::TYPE nextSceneType = sceneNS::NONE;
	sceneNS::SceneData sceneData = sceneNS::SceneData();

public:
	sceneNS::TYPE getSceneType() { return sceneType; }
	sceneNS::TYPE getNextSceneType() { return nextSceneType; }
	sceneNS::SceneData getSceneData() { return sceneData; }

	void setSceneType(sceneNS::TYPE st) { sceneType = st; }
	void setNextSceneType(sceneNS::TYPE nst) { nextSceneType = nst; }
	void setSceneData(sceneNS::SceneData sd) { sceneData = sd; }

 	void clearNextSceneType() { nextSceneType = sceneNS::NONE; }

	virtual ~Scene() {}

	virtual void initialize(sceneNS::SceneData sd) = 0;
	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};

#endif