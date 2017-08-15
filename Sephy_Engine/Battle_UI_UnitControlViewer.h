#ifndef _BATTLE_UI_UNITCONTROL_VIEWER_H
#define _BATTLE_UI_UNITCONTROL_VIEWER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UnitControlViewer;

#include "systemUIDialog.h"

namespace battleUIUnitControlViewerNS
{
	const std::string ERROR_MESSAGE = "Battle Unit Control Viewer Initialize Failed";
	const std::string CONTROL_VIEWER_BACKGROUND = "Ship_Information_Background";
	//========================================================
	const float CONTROL_VIEWER_RELATE_X = -303; // mean :: g_fScreenWidth - 303
	const float CONTROL_VIEWER_RELATE_Y = -203; // mean :: g_fScreenHeight - 203
	const float CONTROL_VIEWER_WIDTH = 292;
	const float CONTROL_VIEWER_HEIGHT = 201;
	//========================================================	
	const char FONT[] = "Courier New";
	const int FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB FONT_COLOR_SHIP_NAME = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
	//========================================================
	const std::string NONE_DATA							= "N/A";
	const std::string INFO_GUIDE_SHIP_NAME				= "SHIP";
	const std::string INFO_GUIDE_SHIP_DP				= "DP";
	const std::string INFO_GUIDE_SHIP_REPAIR_SPPED		= "REPAIR_SPEED";
	const std::string INFO_GUIDE_SHIP_ENGINE_SPEED		= "ENGINE SPEED";
	const std::string INFO_GUIDE_SHIP_ROTATE_SPEED		= "ROTATE SPEED";
	const std::string INFO_GUIDE_SHIP_FLEETNAME			= "FLLET";
	const float INFO_GUIDE_START_X	= 17.f;
	const float INFO_GUIDE_START_Y	= 36.f;
	const float INFO_GUIDE_WIDTH	= 120.f;
	const float INFO_GUIDE_HEIGHT	= 15.f;
	const float INFO_VALUE_START_X	= 150.f;
	const float INFO_VALUE_START_Y	= 36.f;
	const float INFO_VALUE_WIDTH	= 120.f;
	const float INFO_VALUE_HEIGHT	= 15.f;
}

class CBattle_Ship;
class CBattle_UI_UnitControlViewer : public SystemUIDialog
{
private:
	Image*			m_pBackground;
	CBattle_Ship*	m_pShip;
	bool			m_bNoneData;
	//==========================================
	// Real Ship Value RECT & std::string
	//==========================================
	std::string m_strShipName;
	std::string m_strShipDP;
	std::string m_strShipEngineSpeed;
	std::string m_strShipRepairSpeed;
	std::string m_strShipRotateSpeed;
	std::string m_strShipFleetName;

	RECT m_rcShipName;
	RECT m_rcShipDP;
	RECT m_rcShipRepairSpeed;
	RECT m_rcShipEngineSpeed;
	RECT m_rcShipRotateSpeed;
	RECT m_rcShipFleetName;
	//==========================================
	// Guide Commnet RECT
	//==========================================
	RECT m_rcShipNameGuide;
	RECT m_rcShipDPGuide;
	RECT m_rcShipEngineSpeedGuide;
	RECT m_rcShipRepairSpeedGuide;
	RECT m_rcShipRotateSpeedGuide;
	RECT m_rcShipFleetNameGuide;
	
public:
	CBattle_UI_UnitControlViewer();
	~CBattle_UI_UnitControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void setupShip(CBattle_Ship* pShip)
	{
		m_pShip = pShip;
		m_bNoneData = false;
	}
	void setupNone(bool bNone)
	{
		m_bNoneData = bNone;
	}
};

#endif // !_BATTLE_UI_UNITCONTROL_VIEWER_H
