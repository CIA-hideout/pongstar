#include "message.h"

Message::Message() {}

Message::Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, int cn) {
	messageType = mt;
	targetType = tt;
	cmdNo = cn;
}

Message::~Message() {}
