#include "effectManager.h"

EffectManager::EffectManager() {}

EffectManager::~EffectManager() {}

// Decrement duration of all currect effects
void EffectManager::update(float frameTime) {
	// Loop through all entities with effects
	for (std::pair<int, std::unordered_map<effectNS::EFFECT_TYPE, float>> entity : entityEffects) {
		// Loop through all effects of current entity
		for (std::pair<effectNS::EFFECT_TYPE, float> currentEffect : entity.second) {
			float newDuration = currentEffect.second - frameTime;

			// Update duration and set to 0 once duration has expired
			entityEffects[entity.first][currentEffect.first] = (newDuration <= 0) ? 0 : newDuration;
		}
	}
}

// Add new effect
void EffectManager::addEffect(int entityId, effectNS::EFFECT_TYPE effectType, float duration) {
	if (entityEffects.count(entityId) == 0) {
		std::unordered_map<effectNS::EFFECT_TYPE, float> currentEffects = {};
		entityEffects.insert({ entityId, currentEffects });
	}

	entityEffects[entityId].insert({ effectType, duration });
}

// Remove an effect
void EffectManager::removeEffect(int entityId, effectNS::EFFECT_TYPE effectType) {
	// Remove effect from entity
	entityEffects[entityId].erase(effectType);
}

// Returns all current effects the entity has
std::unordered_map<effectNS::EFFECT_TYPE, float> EffectManager::getCurrentEffects(int entityId) {
	std::unordered_map<effectNS::EFFECT_TYPE, float> currentEffects = {};

	if (entityEffects.count(entityId) != 0) {
		currentEffects = entityEffects[entityId];
	}

	return currentEffects;
}