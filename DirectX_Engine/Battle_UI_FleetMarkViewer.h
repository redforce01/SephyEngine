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
	const float FLEET_MARK_VIEW_WIDTH = 140;
	const float FLEET_MARK_VIEW_HEIGHT = 260;
	const float FLEET_MARK_MAX_COUNT = 8;
	const float FLEET_MARK_INVISIBLE_X = -100;
	const float FLEET_ANIME_SPEED = 240.f;

	const std::string ARROW_FILENAME = "FleetListArrow";

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
	Image* m_pArrow;
private:
	bool	m_bAnime;
	bool	m_bVisibleView;
	int		m_nSelectedFleet;
public:
	CBattle_UI_FleetMarkViewer();
	~CBattle_UI_FleetMarkViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//==========================================
	// Member Functions
	//==========================================
	void setArrowAtMark(int nMark)
	{
		float markRight = m_vFleetMarks[nMark]->getFleetMarkRect().right;
		float markCenterHeight = m_vFleetMarks[nMark]->getFleetMarkRect().top + (m_vFleetMarks[nMark]->getHeight() / 2);
		m_pArrow->setX(markRight + 2);
		m_pArrow->setY(markCenterHeight - (m_pArrow->getHeight() / 2));
		m_nSelectedFleet = nMark;
	}
	
	//==========================================
	// Getter Functions
	//==========================================
	vFLEET_MARK getFleetMarks() const
	{
		return m_vFleetMarks;
	}

	int getSelectedFleet() const
	{
		return m_nSelectedFleet;
	}
};

#endif // !_BATTLE_UI_FLEETMARKVIEW_H
