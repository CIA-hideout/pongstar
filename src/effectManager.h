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

class EffectManager {
private:
	std::unordered_map<int, std::unordered_map<effectNS::EFFECT_TYPE, float>> entityEffects;

public:
	EffectManager();
	~EffectManager();

	void update(float frameTime);
	void addEffect(int entityId, effectNS::EFFECT_TYPE effectType, float duration);
	void removeEffect(int entityId, effectNS::EFFECT_TYPE effectType);
	std::unordered_map<effectNS::EFFECT_TYPE, float> getCurrentEffects(int entityId);
};

#endif
