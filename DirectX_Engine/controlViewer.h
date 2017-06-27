#ifndef _CONTROLVIEWER_H
#define _CONTROLVIEWER_H

class ControlViewer;

#include "systemUIDialog.h"
#include "control_SaveButton.h"

namespace toolControlViewerNS
{
	const UINT WIDTH = 500;						// width of treeViewer
	const UINT HEIGHT = 50;						// height of treeViewer
	const UINT X = (WINSIZEX / 2) - WIDTH / 2;	// Viewer location X
	const UINT Y = WINSIZEY - 200;				// Viewer location Y
	const UINT MARGIN = 4;						// text margin from Viewer edge
	const char FONT[] = "Courier New";			// Viewer font
	const int FONT_HEIGHT = 14;					// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const int controlIDSave = 1;
	const int controlIDLoad = 2;
}

class ControlViewer : public SystemUIDialog
{
private:
	Control_SaveButton* m_pSaveButton;

public:
	ControlViewer();
	~ControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	

	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pSaveButton->setMemoryLinkMapSystem(pMapSystem); }
};

#endif // !_CONTROLVIEWER_H
