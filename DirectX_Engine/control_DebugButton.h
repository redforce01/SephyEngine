#ifndef _CONTROLDEBUGBUTTON_H
#define _CONTROLDEBUGBUTTON_H

class Control_DebugButton;

#include "systemUIButton.h"

namespace debugButtonNS
{
	const std::string NAME = "DEBUG";
	const std::string FILENAME = "DebugButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 10;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;
}

class MapSystem;
class Control_DebugButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;

public:
	Control_DebugButton();
	~Control_DebugButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

	// MapSystem MemoryLink Connect
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionDebug(void * obj);
};

#endif // !_CONTROLDEBUGBUTTON_H
