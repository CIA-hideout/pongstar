// Interface class for implementing scenes

#ifndef _SCENE_H
#define _SCENE_H

#include "paddle.h"

namespace sceneNS {
	enum TYPE {
		CLASSIC, TIME_ATK, HIGH_SCORES, CREDITS, VICTORY, NONE
	};

	struct SceneData {	// data to be passed down scene to scene
		paddleNS::SIDE winner;
		TYPE modePlayed;
	};
}

class Scene {
protected:
	sceneNS::TYPE nextSceneType = sceneNS::NONE;
	sceneNS::SceneData sceneData = sceneNS::SceneData();
public:
	sceneNS::TYPE getNextSceneType() { return nextSceneType; }
	sceneNS::SceneData getSceneData() { return sceneData; }

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