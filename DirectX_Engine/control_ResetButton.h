#pragma once
#ifndef _CONTROLRESETBUTTON_H
#define _CONTROLRESETBUTTON_H

class Control_ResetButton;

#include "systemUIButton.h"

namespace resetButtonNS
{
	const std::string NAME = "RESET";
	const std::string FILENAME = "ResetButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;
}

class LogViewer;
class MapSystem;
class Control_ResetButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	LogViewer* m_pLogViewer;
public:
	Control_ResetButton();
	~Control_ResetButton();

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
	static void functionReset(void * obj);
};

#endif // !_CONTROLRESETBUTTON_H