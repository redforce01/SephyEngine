#ifndef _BATTLE_UI_UNITCONTROL_VIEWER_H
#define _BATTLE_UI_UNITCONTROL_VIEWER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UnitControlViewer;

#include "systemUIDialog.h"
#include "systemButton.h"

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
	//========================================================
	const float INFO_GUIDE_SHIP_RANK_MARK_RELATE_X = 120.f;
	const float INFO_GUIDE_SHIP_RANK_MARK_RELATE_Y = 40.f;
	const std::string SHIP_RANK_DEFAULT = "S_6CW";
	const std::string SHIP_RANK_SMALL_KEY = "S_";
	//========================================================
	const std::string AAGUN_BUTTON_NAME = "AAGun";
	const std::string GUN_BUTTON_NAME = "Gun";
	const float GUN_BUTTON_RELATE_X = 210.f;
	const float GUN_BUTTON_RELATE_Y = 140.f;
	const float AAGUN_BUTTON_RELATE_X = 210.f;
	const float AAGUN_BUTTON_RELATE_Y = 160.f;
	const std::string GUN_STATE_ON		= "GUN ON";
	const std::string GUN_STATE_OFF		= "GUN OFF";
	const std::string AAGUN_STATE_ON	= "AA ON";
	const std::string AAGUN_STATE_OFF	= "AA OFF";
	const float GUN_STATE_MESSAGE_RELATE_X	= 150.f;
	const float GUN_STATE_MESSAGE_RELATE_Y	= 140.f;
	const float GUN_STATE_MESSAGE_WIDTH		= 80.f;
	const float GUN_STATE_MESSAGE_HEIGHT	= 17.f;
	const float AAGUN_STATE_MESSAGE_RELATE_X	= 150.f;
	const float AAGUN_STATE_MESSAGE_RELATE_Y	= 160.f;
	const float AAGUN_STATE_MESSAGE_WIDTH		= 80.f;
	const float AAGUN_STATE_MESSAGE_HEIGHT		= 17.f;
	//========================================================
	const std::string ENGINE_STATE_SIGN_NAME_ON		= "onSign";
	const std::string ENGINE_STATE_SIGN_NAME_OFF	= "offSign";
	const std::string ENGINE_BUTTON_NAME			= "Engine_";
	const UINT ENGINE_BUTTON_MAX_FRAME				= 3;
	const std::string ENGINE_BUTTON_STATE_ON		= "EngineFix ON";
	const std::string ENGINE_BUTTON_STATE_OFF		= "EngineFix OFF";
	const float ENGINE_BUTTON_RELATE_X	= 120.f;
	const float ENGINE_BUTTON_RELATE_Y	= 140.f;
	const float ENGINE_STATE_SIGN_RELATE_X	= 90.f;
	const float ENGINE_STATE_SIGN_RELATE_Y	= 155.f;
	const float ENGINE_STATE_MESSAGE_RELATE_X = 17.f;
	const float ENGINE_STATE_MESSAGE_RELATE_Y = 135.f;
	const float ENGINE_STATE_MESSAGE_WIDTH = 100.f;
	const float ENGINE_STATE_MESSAGE_HEIGHT = 17.f;
}

class CBattle_Ship;
class CBattle_UI_UnitControlViewer : public SystemUIDialog
{
private:
	Image*			m_pBackground;
	Image*			m_pShipRankMark;
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
private:
	SystemButton* m_pGunButton;
	SystemButton* m_pAAGunButton;
	bool m_bAutoGunOnOff;
	bool m_bAutoAAGunOnOff;
	RECT m_rcAutoGunStateMessage;
	RECT m_rcAutoAAGunStateMessage;
	std::string m_strAutoGunStateMessage;
	std::string m_strAutoAAGunStateMessage;
private:
	Image*		m_pEngineButton;
	Image*		m_pEngineState;
	int			m_nEngineBtnSpriteNumber;
	bool		m_bFixedEngineOnOff;
	std::string m_strEngineStateMessage;
	RECT		m_rcEngineStateMessage;

public:
	CBattle_UI_UnitControlViewer();
	~CBattle_UI_UnitControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//================================================
	// Member Functions
	//================================================

	void setupShip(CBattle_Ship* pShip)
	{
		m_pShip = pShip;
		m_bNoneData = false;
	}
	void setupNone(bool bNone)
	{
		m_bNoneData = bNone;	
	}

	void setupShipEngineOnOff();

	//================================================
	// Button Static Functions
	//================================================

	static void functionGunButton();
	static void functionAAGunButton();
};

#endif // !_BATTLE_UI_UNITCONTROL_VIEWER_H
