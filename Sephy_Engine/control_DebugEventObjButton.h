#ifndef _CONTROL_DEBUG_EVENT_OBJECT_H
#define _CONTROL_DEBUG_EVENT_OBJECT_H

class Control_DebugEventObjButton;

#include "systemUIButton.h"

namespace debugEventObjectButtonNS
{
	const std::string NAME = "EVENT";
	const std::string FILENAME = "DebugButton2";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;

	const std::string LOG_ON = "DEBUG EVENT OBJECT VIEW ON";
	const std::string LOG_OFF = "DEBUG EVENT OBJECT VIEW OFF";
}

class LogViewer;
class MapSystem;
class Control_DebugEventObjButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	LogViewer* m_pLogViewer;

public:
	Control_DebugEventObjButton();
	~Control_DebugEventObjButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// MapSystem MemoryLink Connect
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
	}
	void setMemoryLinkLogViewer(LogViewer* pLogViewer)
	{
		m_pLogViewer = pLogViewer;
	}
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionDebugEventObject(void * obj);
};

#endif // !_CONTROL_DEBUG_EVENT_OBJECT_H