#include "message.h"

Message::Message() {}

// constructor for pickup messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::PICKUP_CMD pc) {
	messageType = mt;
	pickupCmd = pc;
}

// constructor for score messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc) {
	messageType = mt;
	targetType = tt;
	scoreCmd = sc;
}

// constructor for add effects messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, float d) {
	messageType = mt;
	targetType = tt;
	effectType = et;
	duration = d;
}

// constructor for run effects messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et) {
	messageType = mt;
	targetType = tt;
	effectType = et;
}

Message::~Message() {}
