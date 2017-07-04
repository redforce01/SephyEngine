#ifndef _LOGVIEWER_H
#define _LOGVIEWER_H

class LogViewer;

#include "systemUIDialog.h"

namespace logViewerNS
{
	const UINT WIDTH = 400;				// width of treeViewer
	const UINT HEIGHT = WINSIZEY;		// height of treeViewer
	const UINT X = WINSIZEX - WIDTH;	// Viewer location X
	const UINT Y = 0;					// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const std::string TILE_FOLDER = "03_Tile";
	const UINT BASIC_TILE_WIDTH = 128;
	const UINT BASIC_TILE_HEIGHT = 64;
	const UINT VIEWER_PAGE_ITEM_MAX = 36;

	const int LEFT_BUTTON_ID = 100;
	const int RIGHT_BUTTON_ID = 101;
	const UINT PAGE_BUTTON_SIZE = 30;
	const UINT PAGE_BUTTON_MARGIN = 0;
}

class LogViewer : public SystemUIDialog
{
private:
	std::deque<std::string> m_arrLog;
	

public:
	LogViewer();
	~LogViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void addLog(std::string message)
	{
		m_arrLog.emplace_front(message);
	}
};

#endif // !_LOGVIEWER_H
