#ifndef _CONTROL_DEBUG_OBJECT_H
#define _CONTROL_DEBUG_OBJECT_H

class Control_DebugObjectButton;

#include "systemUIButton.h"

namespace debugObjectButtonNS
{
	const std::string NAME = "OBJECT";
	const std::string FILENAME = "DebugButton2";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;

	const std::string LOG_ON = "DEBUG OBJECT VIEW ON";
	const std::string LOG_OFF = "DEBUG OBJECT VIEW OFF";
}

class LogViewer;
class MapSystem;
class Control_DebugObjectButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	LogViewer* m_pLogViewer;

public:
	Control_DebugObjectButton();
	~Control_DebugObjectButton();

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
	static void functionDebugObject(void * obj);
};

#endif // !_CONTROL_DEBUG_OBJECT_H
