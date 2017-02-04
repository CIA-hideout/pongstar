// Interface class for implementing scenes

#ifndef _SCENE_H
#define _SCENE_H

namespace sceneNS {
	enum TYPE {
		CLASSIC, TIME_ATK, HIGH_SCORES, CREDITS
	};
}

class Scene {
protected:
	sceneNS::TYPE* nextSceneType = NULL;
public:
	sceneNS::TYPE* getNextSceneType() { return nextSceneType; }
	void clearNextSceneType() { nextSceneType = NULL; }

	virtual ~Scene() {}

	virtual void initialize() = 0;
	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};

#endif