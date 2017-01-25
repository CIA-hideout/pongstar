#include "effectManager.h"

EffectManager::EffectManager() {}

EffectManager::~EffectManager() {}

// Decrement duration of all currect effects
void EffectManager::update(float frameTime) {
	for (effectDurationPair curr : entityEffects) {
		float newDuration = curr.second - frameTime;

		entityEffects[curr.first] = (newDuration <= 0) ? 0 : newDuration;
	}
}

// Add new effect
void EffectManager::addEffect(effectNS::EFFECT_TYPE effectType, float duration) {
	entityEffects.insert({ effectType, duration });
}

// Remove an effect
void EffectManager::removeEffect(effectNS::EFFECT_TYPE effectType) {
	entityEffects.erase(effectType);
}