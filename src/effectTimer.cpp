#include "effectTimer.h"

EffectTimer::EffectTimer() {
	elapsedTime = 0.0f;
};

EffectTimer::~EffectTimer() {};

void EffectTimer::update(float frameTime) {
	if (started)
		elapsedTime += frameTime;
}

void EffectTimer::startTimer() {
	started = true;
}

void EffectTimer::resetTimer() {
	started = false;
	elapsedTime = 0.0f;
}
