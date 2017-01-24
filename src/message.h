#ifndef _MESSAGE_H
#define _MESSAGE_H

namespace messageNS {
	enum MESSAGE_TYPE { SCORE };
	enum TARGET_TYPE { LEFT_P, RIGHT_P, ALL_P, BALL };
	//enum class SCORE_CMD: int { INCREMENT=1 };
}

class Message {
private:
	messageNS::MESSAGE_TYPE messageType;
	messageNS::TARGET_TYPE targetType;
	int cmdNo;

public:
	Message();
	Message(messageNS::MESSAGE_TYPE mt, messageNS::TARGET_TYPE tt, int cn);
	~Message();

	messageNS::MESSAGE_TYPE getMessageType() { return messageType; }
	messageNS::TARGET_TYPE getTargetType() { return targetType; }
	int getCmdNo() { return cmdNo; }

	void setMessageType(messageNS::MESSAGE_TYPE mt) { messageType = mt; }
	void setTargetType(messageNS::TARGET_TYPE tt) { targetType = tt; }
	void setCmdNo(int c) { cmdNo = c; }
};

#endif