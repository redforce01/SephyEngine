#include "stdafx.h"
#include "gocMessageManager.h"


GOCMessageManager::GOCMessageManager()
{
}


GOCMessageManager::~GOCMessageManager()
{
}

GOCMessage GOCMessageManager::beginMessage()
{	
	iterMessage = arrMessage.begin();

	return iterMessage->second;
}

GOCMessage GOCMessageManager::nextMessage()
{
	++iterMessage;
	if(iterMessage != arrMessage.end())
		return iterMessage->second;

	return GOCMessage( eGOCMessage::MESSAGE_TYPE_NONE );
}

void GOCMessageManager::resetMessages()
{
	arrMessage.clear();
}
