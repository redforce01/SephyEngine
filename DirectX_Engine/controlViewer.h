#ifndef _CONTROLVIEWER_H
#define _CONTROLVIEWER_H

class ControlViewer;

#include "systemUIDialog.h"
#include "control_ButtonInfo.h"
#include "control_SaveButton.h"
#include "control_LoadButton.h"
#include "control_ResetButton.h"
#include "control_DebugButton.h"
#include "control_PerformButton.h"

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
}

class ControlViewer : public SystemUIDialog
{
private:
	Control_SaveButton* m_pSaveButton;
	Control_LoadButton* m_pLoadButton;
	Control_ResetButton* m_pResetButton;
	Control_DebugButton* m_pDebugButton;
	Control_PerformButton* m_pPerformButton;

public:
	ControlViewer();
	~ControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void setMemoryLinkStatsViewer(StatsViewer* pStatsViewer)
	{
		m_pPerformButton->setMemoryLinkStatsViewer(pStatsViewer);
	}
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pSaveButton->setMemoryLinkMapSystem(pMapSystem);
		m_pLoadButton->setMemoryLinkMapSystem(pMapSystem);
		m_pDebugButton->setMemoryLinkMapSystem(pMapSystem);
		m_pResetButton->setMemoryLinkMapSystem(pMapSystem);
	}
};

#endif // !_CONTROLVIEWER_H
