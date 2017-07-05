#ifndef _LOGVIEWER_H
#define _LOGVIEWER_H

class LogViewer;

#include "systemUIDialog.h"

namespace logViewerNS
{
	const UINT WIDTH = 400;					// width of treeViewer
	const UINT HEIGHT = 250;				// height of treeViewer
	const UINT X = 405;						// Viewer location X
	const UINT Y = WINSIZEY - HEIGHT - 5;	// Viewer location Y
	const UINT MARGIN = 4;					// text margin from Viewer edge
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const std::string LOGBOX_TITLE = "Log";
	const UINT LOG_HEIGHT = 15;
}

class LogViewer : public SystemUIDialog
{
private:
	std::deque<std::string> m_arrLog;
	RECT m_rcLogBox;
	RECT m_rcTitle;
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
