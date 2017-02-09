#ifndef _EFFECTS_H
#define _EFFECTS_H

#include <queue>
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

struct EffectDuration {
	effectNS::EFFECT_TYPE effectType;
	float duration;

	EffectDuration() {}
	EffectDuration(effectNS::EFFECT_TYPE et, float d) : effectType(et), duration(d) {}
};

typedef std::pair<effectNS::EFFECT_TYPE, float> effectDurationPair;
typedef std::unordered_map<effectNS::EFFECT_TYPE, float> effectDurations;

// startEffectQueue -> currentEffects
class Effects {
private:
	std::queue<EffectDuration> startEffectQueue;
	std::queue<EffectDuration> endEffectQueue;
	effectDurations currentEffects;
public:
	Effects();
	~Effects();

	// getters
	effectDurations getEffects() { return currentEffects; }
	std::queue<EffectDuration> getStartEffectQueue() { return startEffectQueue; }
	std::queue<EffectDuration> getEndEffectQueue() { return endEffectQueue; }
	
	// setters
	void setEffects(effectDurations ed) { currentEffects = ed; }
	void setStartEffectQueue(std::queue<EffectDuration> seq) { startEffectQueue = seq; }
	void setEndEffectQueue(std::queue<EffectDuration> eeq) { endEffectQueue = eeq; }

	void update(float frameTime);
	void addEffect(effectNS::EFFECT_TYPE effectType, float duration);
	void removeEffect(effectNS::EFFECT_TYPE effectType);

	void popStartEffectQueue();
	EffectDuration frontEffectQueue() { return startEffectQueue.front(); }
	
	void popEndEffectQueue();
};

#endif
