#ifndef _ENGINEWINDOWMANAGER_H
#define _ENGINEWINDOWMANAGER_H

class EngineWindowManager;

#include "cSingletonBase.h"
#include <map>
#include <string>
#include "engineWindow.h"

class EngineWindowManager : public cSingletonBase<EngineWindowManager>
{
private:
	typedef std::map<std::string, EngineWindow*> MAP_ENGINE_WINDOW;

private:
	MAP_ENGINE_WINDOW engineWindows;
	
public:
	EngineWindowManager();
	~EngineWindowManager();

	void addWindow(std::string windowName, EngineWindow* pWindow);
	void resetHwndPos();

	HWND getHwnd(std::string windowName);
	EngineWindow* getWindow(std::string windowName);
	int getHwndWidth(std::string windowName);
	int getHwndHeight(std::string windowName);
	
};

#define ENGINE_WINDOW_MANAGER EngineWindowManager::GetInstance()

#endif // !_ENGINEWINDOWMANAGER_H

