#include "stdafx.h"
#include "engineWindowManager.h"


EngineWindowManager::EngineWindowManager()
{
}


EngineWindowManager::~EngineWindowManager()
{
}

void EngineWindowManager::addWindow(std::string windowName, EngineWindow * pWindow)
{
	engineWindows.emplace(windowName, pWindow);
}

void EngineWindowManager::resetHwndPos()
{
	HDWP hDwp = BeginDeferWindowPos(engineWindows.size());

	for (auto iter : engineWindows)
	{
		hDwp = DeferWindowPos(hDwp, iter.second->getHwnd(), NULL, 
			iter.second->getBasicX(), iter.second->getBasicY(),
			iter.second->getWidth(), iter.second->getHeight(), SWP_NOZORDER);
	}
	EndDeferWindowPos(hDwp);
}

HWND EngineWindowManager::getHwnd(std::string windowName)
{
	for (auto iter : engineWindows)
	{
		if ((iter.first.compare(windowName) == 0))
		{
			return iter.second->getHwnd();
		}
	}

	return nullptr;
}

EngineWindow * EngineWindowManager::getWindow(std::string windowName)
{
	for (auto iter : engineWindows)
	{
		if ((iter.first.compare(windowName) == 0))
		{
			return iter.second;
		}
	}

	return nullptr;
}

int EngineWindowManager::getHwndWidth(std::string windowName)
{
	for (auto iter : engineWindows)
	{
		if ((iter.first.compare(windowName) == 0))
		{
			return iter.second->getWidth();
		}
	}

	return 0;
}

int EngineWindowManager::getHwndHeight(std::string windowName)
{
	for (auto iter : engineWindows)
	{
		if ((iter.first.compare(windowName) == 0))
		{
			return iter.second->getHeight();
		}
	}

	return 0;
}
