#ifndef _CONTROLPERFORMBUTTON_H
#define _CONTROLPERFORMBUTTON_H

class Control_PerformButton;

#include "systemUIButton.h"

namespace performButtonNS
{
	const std::string NAME = "STATS";
	const std::string FILENAME = "PerformanceButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 30;
}

class LogViewer;
class StatsViewer;
class Control_PerformButton : public SystemUIButton
{
private:
	StatsViewer* m_pStatsViewer;
	LogViewer* m_pLogViewer;
public:
	Control_PerformButton();
	~Control_PerformButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();
	
	void setMemoryLinkStatsViewer(StatsViewer* pStatsViewer)
	{ m_pStatsViewer = pStatsViewer; }
	void setMemoryLinkLogViewer(LogViewer* pLogViewer)
	{ m_pLogViewer = pLogViewer; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionPerform(void * obj);
};

#endif // !_CONTROLPERFORMBUTTON_H
