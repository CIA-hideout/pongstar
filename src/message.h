#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "effects.h"

namespace messageNS {
	enum MESSAGE_TYPE { SCORE, PICKUP, ADD_EFFECT, RUN_EFFECT, END_EFFECT, MAGNET_EFFECT };
	enum TARGET_TYPE { LEFT_P, RIGHT_P, BOTH_P, BALL, NONE };
	enum SCORE_CMD { INCREMENT };
	enum PICKUP_CMD { MOVE_LEFT, MOVE_RIGHT };
	enum MAGNET_CMD { BIND, UNBIND };
}

class Message {
private:
	messageNS::MESSAGE_TYPE messageType;
	messageNS::TARGET_TYPE targetType;
	messageNS::SCORE_CMD scoreCmd;
	messageNS::PICKUP_CMD pickupCmd;
	messageNS::MAGNET_CMD magnetCmd;
	effectNS::EFFECT_TYPE effectType;
	float duration;
	int entityId;	// entity that sent the message

	int paddleId;	// magnet effect
	int ballId;		// magnet effect

public:
	Message();
	Message(messageNS::MESSAGE_TYPE mt, messageNS::PICKUP_CMD pc); // pickup
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc, int id); // score
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, int id, float duration); // add effect
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, int id); // run effects and end effects

	// Specific effects
	Message(messageNS::MESSAGE_TYPE mt, messageNS::MAGNET_CMD mc, int paddleId, int ballId);

	~Message();

	// Getters
	messageNS::MESSAGE_TYPE getMessageType() { return messageType; }
	messageNS::TARGET_TYPE getTargetType() { return targetType; }
	messageNS::SCORE_CMD getScoreCmd() { return scoreCmd; }
	messageNS::PICKUP_CMD getPickupCmd() { return pickupCmd; }
	messageNS::MAGNET_CMD getMagnetCmd() { return magnetCmd; }
	effectNS::EFFECT_TYPE getEffectType() { return effectType; }
	float getDuration() { return duration; }
	int getEntityId() { return entityId; }
	int getPaddleId() { return paddleId; }
	int getBallId() { return ballId; }

	// Setters
	void setMessageType(messageNS::MESSAGE_TYPE mt) { messageType = mt; }
	void setTargetType(messageNS::TARGET_TYPE tt) { targetType = tt; }
	void setScoreCmd(messageNS::SCORE_CMD sc) { scoreCmd = sc; }
	void setPickupCmd(messageNS::PICKUP_CMD pc) { pickupCmd = pc; }
	void setMagnetCmd(messageNS::MAGNET_CMD mc) { magnetCmd = mc; }
	void setEffectType(effectNS::EFFECT_TYPE et) { effectType = et; }
	void setDuration(float d) { duration = d; }
	void setEntityId(int id) { entityId = id; }
	void setPaddleId(int id) { paddleId = id; }
	void setBallId(int id) { ballId = id; }
};

#endif
