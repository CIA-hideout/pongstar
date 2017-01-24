#include "message.h"

Message::Message() {}

// generic constructor for any messages
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, int cn) {
	messageType = mt;
	targetType = tt;
	cmdNo = cn;
}

// constructor for effects
Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, effectNS::EFFECT_TYPE et) {
	messageType = mt;
	targetType = tt;
	effectType = et;
}

Message::~Message() {}
