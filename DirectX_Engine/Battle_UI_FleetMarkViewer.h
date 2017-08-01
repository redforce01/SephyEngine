#ifndef _BATTLE_UI_FLEETMARKVIEW_H
#define _BATTLE_UI_FLEETMARKVIEW_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetMarkViewer;

#include "systemUIDialog.h"
#include "Battle_UI_FleetMark.h"

namespace battleFleetMarkViewerNS
{
	const std::string ERROR_MESSAGE = "Battle Fleet Mark View Initialize Failed";
	const float FLEET_MARK_VIEW_X = 0;
	const float FLEET_MARK_VIEW_Y = 320;
	const float FLEET_MARK_VIEW_WIDTH = 120;
	const float FLEET_MARK_VIEW_HEIGHT = 260;
	const float FLEET_MARK_MAX_COUNT = 8;

	const float FLEET_MARK_INVISIBLE_X = -100;

	const float FLEET_ANIME_SPEED = 240.f;


	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR_ACTIVE = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const COLOR_ARGB BACK_COLOR_DEACTIVE = SETCOLOR_ARGB(255, 26, 32, 44);
}

class CBattle_UI_FleetMarkViewer : public SystemUIDialog
{
	typedef std::vector<CBattle_UI_FleetMark*> vFLEET_MARK;
private:
	vFLEET_MARK m_vFleetMarks;

private:
	bool m_bAnime;
	bool m_bVisibleView;

public:
	CBattle_UI_FleetMarkViewer();
	~CBattle_UI_FleetMarkViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//==========================================
	// Member Functions
	//==========================================

	
	//==========================================
	// Getter Functions
	//==========================================
	vFLEET_MARK getFleetMarks() const
	{
		return m_vFleetMarks;
	}
};

#endif // !_BATTLE_UI_FLEETMARKVIEW_H
