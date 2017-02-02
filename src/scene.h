// Interface class for implementing scenes

#ifndef _SCENE_H
#define _SCENE_H

class Scene {
public:
	virtual ~Scene() {}

	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};

#endif