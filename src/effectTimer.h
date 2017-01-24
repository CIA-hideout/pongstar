#ifndef _EFFECTTIMER_H
#define _EFFECTTIMER_H

#include "effectTimer.h"

class EffectTimer {
private:
	float elapsedTime;
	bool started;
	float duration;

public:
	EffectTimer();
	~EffectTimer();

	float getElapsedTime() { return elapsedTime; };
	void setElapsedTime(float et) { elapsedTime = et; }

	void startTimer();
	void resetTimer();
	
	void update(float frameTime);
};

#endif