#ifndef _CONTROLLOADBUTTON_H
#define _CONTROLLOADBUTTON_H

class Control_LoadButton;

#include "systemUIButton.h"

namespace loadButtonNS
{
	const std::string NAME = "LOAD";
	const std::string FILENAME = "LoadButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 26;
}

class LogViewer;
class MapSystem;
class Control_LoadButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	LogViewer* m_pLogViewer;
public:
	Control_LoadButton();
	~Control_LoadButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

	// MapSystem MemoryLink Connect
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
	void setMemoryLinkLogViewer(LogViewer* pLogViewer)
	{ m_pLogViewer = pLogViewer; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionLoad(void * obj);
};

#endif // !_CONTROLLOADBUTTON_H