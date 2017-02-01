#ifndef _EFFECTS_H
#define _EFFECTS_H

#include <unordered_map>

namespace effectNS {
	const enum EFFECT_TYPE { MAGNET, INVERT, SHIELD, MULTIPLY, BOOST, SLOW, SHRINK, ENLARGE, MYSTERY };

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

class Effects {
private:
	effectDurations currentEffects;

public:
	Effects();
	~Effects();

	// getters
	effectDurations getEffects() { return currentEffects; }
	
	// setters
	void setEffects(effectDurations ed) { currentEffects = ed; }

	void update(float frameTime);
	void addEffect(effectNS::EFFECT_TYPE effectType, float duration);
	void removeEffect(effectNS::EFFECT_TYPE effectType);
};

#endif
