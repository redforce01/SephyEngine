#pragma once

enum class eGOCMessage
{
	MESSAGE_TYPE_NONE,
	MESSAGE_TYPE_POSITION
};

class GOCMessage
{
	eGOCMessage messageType;

public:
	GOCMessage(eGOCMessage msgType);
	~GOCMessage();

	eGOCMessage getType() { return messageType; }
};

