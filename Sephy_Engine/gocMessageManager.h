#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H
#define WIN32_LEAN_AND_MEAN

class MessageManager;

#include "gocMessage.h"
#include <map>

class GOCMessageManager
{
private:
	typedef std::multimap<eGOCMessage, GOCMessage> MSG_CONTAINER;		//multi map Container

private:
	MSG_CONTAINER				arrMessage;
	MSG_CONTAINER::iterator		iterMessage;

public:
	GOCMessageManager();
	~GOCMessageManager();

	GOCMessage beginMessage();
	GOCMessage nextMessage();

	void resetMessages();
};

#endif // !_MESSAGEMANAGER_H
