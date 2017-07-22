#ifndef _CONTROL_DEBUG_CELL_BUTTON_H
#define _CONTROL_DEBUG_CELL_BUTTON_H

class Control_DebugCellButton;

#include "systemUIButton.h"

namespace debugcellButtonNS
{
	const std::string NAME = "CELL";
	const std::string FILENAME = "DebugButton2";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;

	const std::string LOG_ON = "DEBUG VIEW CELLS ON";
	const std::string LOG_OFF = "DEBUG VIEW CELLS OFF";
}

class LogViewer;
class MapSystem;
class Control_DebugCellButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	LogViewer* m_pLogViewer;

public:
	Control_DebugCellButton();
	~Control_DebugCellButton();

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
	static void functionDebugCell(void * obj);
};

#endif // !_CONTROL_DEBUG_CELL_BUTTON_H