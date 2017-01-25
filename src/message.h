#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "effectManager.h"

namespace messageNS {
	enum MESSAGE_TYPE { SCORE, EFFECT };
	enum TARGET_TYPE { LEFT_P, RIGHT_P, ALL_P, BALL };
	enum SCORE_CMD { INCREMENT };
}

class Message {
private:
	messageNS::MESSAGE_TYPE messageType;
	messageNS::TARGET_TYPE targetType;
	messageNS::SCORE_CMD scoreCmd;

	effectNS::EFFECT_TYPE effectType;
	float duration;

public:
	Message();	
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc); // score
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, float duration); // effect

	~Message();

	messageNS::MESSAGE_TYPE getMessageType() { return messageType; }
	messageNS::TARGET_TYPE getTargetType() { return targetType; }
	messageNS::SCORE_CMD getScoreCmd() { return scoreCmd; }
	effectNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }

	void setMessageType(messageNS::MESSAGE_TYPE mt) { messageType = mt; }
	void setTargetType(messageNS::TARGET_TYPE tt) { targetType = tt; }
	void setScoreCmd(messageNS::SCORE_CMD sc) { scoreCmd = sc; }
	void setEffectType(effectNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }
};

#endif