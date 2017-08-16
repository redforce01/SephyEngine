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
	const float FLEET_MAKE_VIEW_X = 0.f; // (mean : g_fScreenWidth - VIEW_WIDTH(300) - VIEW_MARGIN(10))
	const float FLEET_MAKE_VIEW_Y = 190.f;
	const float FLEET_MAKE_VIEW_WIDTH = 220.f;
	const float FLEET_MAKE_VIEW_HEIGHT = 300.f;
	const float FLEET_MAKE_VIEW_MARGIN = 10.f;
	//=====================================================================
	const float FLEET_MAKE_VIEW_SPEED = 400.f;
	const float FLEET_MAKE_VIEW_INVISIBLE_X = 0; // (mean : g_fScreenWidth + VIEW_WIDTH(220) - MARGIN(20))
	const float FLEET_MAKE_VIEW_INVISIBLE_MARGIN = 20.f;
	//=====================================================================
	const std::string FLEET_FLAG_SHIP_MESSAGE_NA = "N/A";
	const std::string FLEET_FLAG_SHIP_TYPE_GUIDE = "TYPE :";
	const std::string FLEET_FLAG_SHIP_NAME_GUIDE = "NAME :";
	const float FLEET_FLAG_SHIP_GUIDE_WIDTH = 40.f;
	const float FLEET_FLAG_SHIP_GUIDE_HEIGHT = 20.f;
	const float FLEET_FLAG_SHIP_GUIDE_BOX_BOTTOM_LINE_WIDTH = 150;
	const float FLEET_FLAG_SHIP_GUIDE_BOX_BOTTOM_MARGIN = 5;
	//=====================================================================
	const std::string FLEET_MAKE_ON_SIGN_KEY = "onSign";
	const std::string FLEET_MAKE_OFF_SIGN_KEY = "offSign";

	//=====================================================================
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR_ACTIVE = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const COLOR_ARGB BACK_COLOR_DEACTIVE = SETCOLOR_ARGB(255, 26, 32, 44);
}

class CBattle_UnitSystem;
class CBattle_UI_FleetMakeViewer : public SystemUIDialog
{
private: // Forward Declaration
	CBattle_UnitSystem* m_pBattleUnitSystem;

private:
	RECT m_rcFlagShipTypeGuide;
	RECT m_rcFlagShipNameGuide;
	RECT m_rcFlagShipTypeMessage;
	RECT m_rcFlagShipNameMessage;
	std::string m_strFlagShipTypeGuide;
	std::string m_strFlagShipNameGuide;
	std::string m_strFlagShipType;
	std::string m_strFlagShipName;
private:
	Image*		m_pFleetMakeSign;
	std::string m_strFleetMakeSignKey;
private:	
	CBattle_UI_FleetMakeButton*		m_pFleetMakeButton;
	CBattle_UI_FleetRemoveButton*	m_pFleetRemoveButton;
	CBattle_UI_FleetSetupButton*	m_pFleetSetupButton;
	CBattle_UI_FlagShipButton*		m_pFlagShipButton;
private:
	bool m_bVisibleView;
	bool m_bFleetMakeMode;
	bool m_bActive;
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

	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}

	//========================================================
	// Member Functions
	//========================================================

	void setFlagShipMessage(std::string strType, std::string strName)
	{
		m_strFlagShipType = strType;
		m_strFlagShipName = strName;
	}

	void setViewVisible(bool bVisible)
	{
		m_bVisibleView = bVisible;
	}

	void setFleetMakeMode(bool bMakeMode)
	{
		m_bFleetMakeMode = bMakeMode;
	}

	void setActive(bool bActive)
	{
		m_bActive = bActive;
	}

	//========================================================
	// Member Functions
	//========================================================

	bool getViewVisible() const
	{
		return m_bVisibleView;
	}

	bool getFleetMakeMode() const
	{
		return m_bFleetMakeMode;
	}
};

#endif // !_BATTLE_UI_FLEETMAKEVIEWER_H
