#include "stdafx.h"
#include "engineCore.h"


EngineCore::EngineCore()
{
	bEngineStart = false;
}


EngineCore::~EngineCore()
{
	for (auto iter : engineThread)
	{
		if (iter.second->joinable())
		{
			iter.second->join();
			SAFE_DELETE(iter.second);
		}
	}
}

void EngineCore::addThread(std::string threadName)
{
	engineThread.emplace(threadName, new std::thread);
}

void EngineCore::removeThread(std::string threadName)
{
	if(engineThread.find(threadName)->second->joinable())
		engineThread.find(threadName)->second->join();
}