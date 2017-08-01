#ifndef _BATTLE_UI_FLEETMAKEVIEWER_H
#define _BATTLE_UI_FLEETMAKEVIEWER_H


#include "systemUIDialog.h"
#include "Battle_UI_FleetMakeButton.h"
#include "Battle_UI_FleetRemoveButton.h"
#include "Battle_UI_FleetSetupButton.h"
#include "Battle_UI_FlagShipButton.h"

namespace battleUIFleetMakeViewerNS
{
	const std::string ERROR_MESSAGE = "Battle UI Fleet Make Viewer Initialize Failed";
	const float FLEET_MAKE_VIEW_X = 0.f; // (mean : g_fScreenWidth - VIEW_WIDTH)
	const float FLEET_MAKE_VIEW_Y = 190.f;
	const float FLEET_MAKE_VIEW_WIDTH = 220.f;
	const float FLEET_MAKE_VIEW_HEIGHT = 300.f;

	const float FLEET_MAKE_VIEW_SPEED = 400.f;
	const float FLEET_MAKE_VIEW_INVISIBLE_X = 0; // (mean : g_fScreenWidth + VIEW_WIDTH(220) - MARGIN(20))

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR_ACTIVE = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const COLOR_ARGB BACK_COLOR_DEACTIVE = SETCOLOR_ARGB(255, 26, 32, 44);
}

class CBattle_UI_FleetMakeViewer : public SystemUIDialog
{
private:	
	CBattle_UI_FleetMakeButton*		m_pFleetMakeButton;
	CBattle_UI_FleetRemoveButton*	m_pFleetRemoveButton;
	CBattle_UI_FleetSetupButton*	m_pFleetSetupButton;
	CBattle_UI_FlagShipButton*		m_pFlagShipButton;
private:
	bool m_bVisibleView;

public:
	CBattle_UI_FleetMakeViewer();
	~CBattle_UI_FleetMakeViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//========================================================
	// Member Functions
	//========================================================

	static void functionFleetMake();
	static void functionFleetRemove();
	static void functionFleetSetup();
	static void functionSetFlagShip();

	void setViewVisible(bool bVisible)
	{
		m_bVisibleView = bVisible;
	}

	bool getViewVisible() const
	{
		return m_bVisibleView;
	}
};

#endif // !_BATTLE_UI_FLEETMAKEVIEWER_H
