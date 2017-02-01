#include "effects.h"

Effects::Effects() {}

Effects::~Effects() {}

// Decrement duration of all currect effects
void Effects::update(float frameTime) {
	for (effectDurationPair curr : currentEffects) {
		float newDuration = curr.second - frameTime;

		currentEffects[curr.first] = (newDuration <= 0) ? 0 : newDuration;
	}
}

// Add new effect
void Effects::addEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	currentEffects.insert({ effectType, duration });
}

// Remove an effect
void Effects::removeEffect(effectNS::EFFECT_TYPE effectType) {
	currentEffects.erase(effectType);
}