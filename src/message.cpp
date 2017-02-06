#include "message.h"

Message::Message() {}

// constructor for MESSAGE_TYPE PICKUP messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::PICKUP_CMD pc) {
	messageType = mt;
	pickupCmd = pc;
}

// constructor for MESSAGE_TYPE SCORE messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc, int id) {
	messageType = mt;
	targetType = tt;
	scoreCmd = sc;
	entityId = id;
}

// constructor for MESSAGE_TYPE ADD_EFFECT messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, int id, float d) {
	messageType = mt;
	targetType = tt;
	effectType = et;
	entityId = id;
	duration = d;
}

// constructor for MESSAGE_TYPE RUN_EFFECT messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, int id) {
	messageType = mt;
	targetType = tt;
	effectType = et;
	entityId = id;
}

Message::~Message() {}
