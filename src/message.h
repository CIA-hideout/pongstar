#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "effects.h"

namespace messageNS {
	enum MESSAGE_TYPE { SCORE, PICKUP, ADD_EFFECT, RUN_EFFECT };
	enum TARGET_TYPE { LEFT_P, RIGHT_P, ALL_P, BALL, NONE };
	enum SCORE_CMD { INCREMENT };
	enum PICKUP_CMD { MOVE_LEFT, MOVE_RIGHT };
}

class Message {
private:
	messageNS::MESSAGE_TYPE messageType;
	messageNS::TARGET_TYPE targetType;
	messageNS::SCORE_CMD scoreCmd;
	messageNS::PICKUP_CMD pickupCmd;

	effectNS::EFFECT_TYPE effectType;
	float duration;

public:
	Message();
	Message(messageNS::MESSAGE_TYPE mt, messageNS::PICKUP_CMD pc); // pickup
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc); // score
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, float duration); // effect
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et);

	~Message();

	// Getters
	messageNS::MESSAGE_TYPE getMessageType() { return messageType; }
	messageNS::TARGET_TYPE getTargetType() { return targetType; }
	messageNS::SCORE_CMD getScoreCmd() { return scoreCmd; }
	messageNS::PICKUP_CMD getPickupCmd() { return pickupCmd; }
	effectNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }

	// Setters
	void setMessageType(messageNS::MESSAGE_TYPE mt) { messageType = mt; }
	void setTargetType(messageNS::TARGET_TYPE tt) { targetType = tt; }
	void setScoreCmd(messageNS::SCORE_CMD sc) { scoreCmd = sc; }
	void setPickupCmd(messageNS::PICKUP_CMD pc) { pickupCmd = pc; }
	void setEffectType(effectNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }
};

#endif