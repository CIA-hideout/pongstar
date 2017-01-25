#ifndef _EFFECTMANAGER_H
#define _EFFECTMANAGER_H

#include <unordered_map>

namespace effectNS {
	const enum EFFECT_TYPE { MAGNET, INVERT, ENLARGE };

	struct EffectData {
		effectNS::EFFECT_TYPE effectType;
		int frame;
		float duration;

		EffectData() {}
		EffectData(effectNS::EFFECT_TYPE et, int f, float d) : effectType(et), frame(f), duration(d) {}
	};
}

typedef std::unordered_map<effectNS::EFFECT_TYPE, float> effectDurations;
typedef std::pair<effectNS::EFFECT_TYPE, float> effectDurationPair;

class EffectManager {
private:
	effectDurations entityEffects;

public:
	EffectManager();
	~EffectManager();

	// getters
	effectDurations getEffects() { return entityEffects; }
	
	// setters
	void setEffects(effectDurations ed) { entityEffects = ed; }

	void update(float frameTime);
	void addEffect(effectNS::EFFECT_TYPE effectType, float duration);
	void removeEffect(effectNS::EFFECT_TYPE effectType);
};

#endif
