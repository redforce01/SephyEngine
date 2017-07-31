#ifndef _BATTLE_UI_FLEETMARKVIEW_H
#define _BATTLE_UI_FLEETMARKVIEW_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetMarkView;

#include "Battle_UI_FleetMark.h"
#include "systemUIDialog.h"
#include <vector>

namespace battleFleetMarkViewNS
{
	const std::string ERROR_MESSAGE = "Battle Fleet Mark View Initialize Failed";
	const UINT FLEET_MARK_VIEW_X = 0;
	const UINT FLEET_MARK_VIEW_Y = 290;
	const UINT FLEET_MARK_VIEW_WIDTH = 120;
	const UINT FLEET_MARK_VIEW_HEIGHT = 260;
	const UINT FLEET_MARK_MAX_COUNT = 8;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR_ACTIVE = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const COLOR_ARGB BACK_COLOR_DEACTIVE = SETCOLOR_ARGB(255, 26, 32, 44);
}

class CBattle_UI_FleetMarkView : public SystemUIDialog
{
	typedef std::vector<CBattle_UI_FleetMark*> vFLEET_MARK;
private:
	vFLEET_MARK m_vFleetMarks;
	
public:
	CBattle_UI_FleetMarkView();
	~CBattle_UI_FleetMarkView();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	vFLEET_MARK getFleetMarks() const
	{
		return m_vFleetMarks;
	}
};

#endif // !_BATTLE_UI_FLEETMARKVIEW_H
