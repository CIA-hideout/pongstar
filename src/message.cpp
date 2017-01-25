#include "message.h"

Message::Message() {}

// generic constructor for any messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, messageNS::SCORE_CMD sc) {
	messageType = mt;
	targetType = tt;
	scoreCmd = sc;
}

// constructor for effects
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et, float d) {
	messageType = mt;
	targetType = tt;
	effectType = et;
	duration = d;
}

Message::~Message() {}
