#include "effects.h"

// After initializing effect, add to effectDurations for maintaining time.
// If an entity gets two same effects, the duration of the effect will increase.
// The update mtd will not push the effect into end queue if time is stil running

Effects::Effects() {}

Effects::~Effects() {}

// Decrement duration of all currect effects
void Effects::update(float frameTime) {
	for (effectDurationPair curr : currentEffects) {
		float newDuration = curr.second - frameTime;

		currentEffects[curr.first] = (newDuration <= 0) ? 0 : newDuration;

		if (newDuration <= 0) {
			endEffectQueue.push(EffectDuration(curr.first, curr.second));
		}
	}
}

// Add new effect
void Effects::addEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	startEffectQueue.push(EffectDuration(effectType, duration));
}

// Remove an effect
void Effects::removeEffect(effectNS::EFFECT_TYPE effectType) {
	currentEffects.erase(effectType);
}

// Start timer after effect has been initialized
void Effects::popStartEffectQueue() {
	EffectDuration ed = startEffectQueue.front();
	bool effectExists = false;

	for (effectDurationPair curr : currentEffects) {
		if (curr.first == ed.effectType)
			effectExists = true;
	}

	if (effectExists)
		currentEffects[ed.effectType] += ed.duration;
	else
		currentEffects[ed.effectType] = ed.duration;

	startEffectQueue.pop();
}

// After effect's duration end, remove from currentEffects and endEffectQueue
void Effects::popEndEffectQueue() {
	currentEffects.erase(endEffectQueue.front().effectType);
	endEffectQueue.pop();
}