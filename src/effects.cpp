#include "effects.h"

// After initializing effect, add to effectDurations for maintaining time.
// If an entity gets two same effects, the duration of the effect will increase.
// The update mtd will not push the effect into end queue if time is stil running

Effects::Effects() {}

Effects::~Effects() {}

bool Effects::effectExists(effectNS::EFFECT_TYPE effectType) {
	for (effectDurationPair curr : currentEffects) {
		if (curr.first == effectType)
			return true;
	}

	return false;
}

bool Effects::isPhysicalEffect(effectNS::EFFECT_TYPE et) {
	return et == effectNS::ENLARGE || et == effectNS::SHRINK || et == effectNS::BOOST || et == effectNS::SLOW;
}

ContrastEffect Effects::findContrastEffect(effectNS::EFFECT_TYPE newEffect) {
	effectNS::EFFECT_TYPE contrastEffect = effectNS::EFFECT_TYPE();
	bool exists = false;

	if (newEffect == effectNS::ENLARGE) {
		contrastEffect = effectNS::SHRINK;
		exists = effectExists(effectNS::SHRINK);
	}
	else if (newEffect == effectNS::SHRINK) {
		contrastEffect = effectNS::ENLARGE;
		exists = effectExists(effectNS::ENLARGE);
	}
	else if (newEffect == effectNS::BOOST) {
		contrastEffect = effectNS::SLOW;
		exists = effectExists(effectNS::SLOW);
	}
	else if (newEffect == effectNS::SLOW) {
		contrastEffect = effectNS::BOOST;
		exists = effectExists(effectNS::BOOST);
	}

	return ContrastEffect(contrastEffect, exists);
}

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
// If effect is already running, do not re-initialize effects
// For accurate timings, initialize effect first, then start timers
void Effects::addEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	ContrastEffect ce = findContrastEffect(effectType);

	if (ce.exists)
		removeEffect(ce.effect);
	
	if (effectExists(effectType))
		currentEffects[effectType] += duration;
	else
		startEffectQueue.push(EffectDuration(effectType, duration));
}

// Remove an effect
void Effects::removeEffect(effectNS::EFFECT_TYPE effectType) {
	currentEffects.erase(effectType);
}

// Start timer after effect has been initialized
// No need check for repeated effect as it has been done in addEffect()
void Effects::popStartEffectQueue() {
	EffectDuration ed = startEffectQueue.front();
	currentEffects[ed.effectType] = ed.duration;
	startEffectQueue.pop();
}

// After effect's duration end, remove from currentEffects and endEffectQueue
void Effects::popEndEffectQueue() {
	currentEffects.erase(endEffectQueue.front().effectType);
	endEffectQueue.pop();
}

void Effects::resetEffects() {
	for (auto& x : currentEffects) {
		if (isPhysicalEffect(x.first))
			endEffectQueue.push(EffectDuration(x.first, x.second));
	}
}