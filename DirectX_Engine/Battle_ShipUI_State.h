#ifndef _BATTLE_SHIPUI_STATE_H
#define _BATTLE_SHIPUI_STATE_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipUI_State;

#include "image.h"

namespace battleShipUIStateNS
{
	const std::string ERROR_MESSAGE = "Battle ShipUI State Interface Initialize Failed";
	const std::string DP_BACKPANNEL_FILENAME	= "dp_backpannel";
	const std::string DP_GUAGE_GREEN_FILENAME	= "guage_green";
	const std::string DP_GUAGE_YELLOW_FILENAME	= "guage_yellow";
	const std::string DP_GUAGE_ORANGE_FILENAME	= "guage_orange";
	const std::string DP_GUAGE_RED_FILENAME		= "guage_red";
	const std::string SHIP_GUIDE_FILENAME		= "shipGuide";
	//==============================================================
	const float STATE_UI_GUIDE_RELATE_X		= 0;
	const float STATE_UI_GUIDE_RELATE_Y		= -50;
	const float STATE_UI_DP_BACK_RELATE_X	= 30;
	const float STATE_UI_DP_BACK_RELATE_Y	= -45;
	const float STATE_UI_PROGRESS_RELATE_X	= 47;
	const float STATE_UI_PROGRESS_RELATE_Y	= -39;
	const float STATE_UI_SHIPRANK_RELATE_X	= -5;
	const float STATE_UI_SHIPRANK_RELATE_Y	= -60;
	const float STATE_UI_SHIPNAME_RELATE_X	= 32;
	const float STATE_UI_SHIPNAME_RELATE_Y	= -60;
	const float STATE_UI_SHIPNAME_BOX_WIDTH = 100;
	const float STATE_UI_SHIPNAME_BOX_HEIGHT = 16;
	//==============================================================
	const float DP_MAX_PROGRESS_WIDTH	= 100.f;
	const float DP_COLOR_RATE_GREEN		= 80.f;
	const float DP_COLOR_RATE_YELLOW	= 50.f;
	const float DP_COLOR_RATE_ORANGE	= 20.f;
	const float DP_COLOR_RATE_RED		= 0.f;
	const float DP_ANIMATION_ACCELATE	= 0.05f;
	//==============================================================
	const std::string SHIP_RANK_CHIEF					= "ChifWarrantOfficer";
	const std::string SHIP_RANK_ENSIGN					= "Ensign";
	const std::string SHIP_RANK_LIEUTENANT_JUNIORGRADE	= "LieutenantJuniorGrade";
	const std::string SHIP_RANK_LIEUTENANT				= "Lieutenant";
	const std::string SHIP_RANK_LIEUTENANT_COMMANDER	= "LieutenantCommander";
	const std::string SHIP_RANK_COMMANDER				= "Commander";
	const std::string SHIP_RANK_CAPTAIN					= "Captain";
	const std::string SHIP_RANK_REAR_ADMIRAL_LOWER		= "RearAdmiralLower";
	const std::string SHIP_RANK_REAR_ADMIRAL_UP			= "RearAdmiralUp";
	const std::string SHIP_RANK_VICE_ADMIRAL			= "ViceAdmiral";
	const std::string SHIP_RANK_ADMIRAL					= "Admiral";
	//==============================================================
	const char			FONT[] = "Courier New";
	const int			FONT_HEIGHT = 14;
	const COLOR_ARGB	FONT_PLAYER_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB	FONT_ENEMY_COLOR = graphicsNS::RED;
	const bool			FONT_BOLD = true;
}

class CBattle_Ship;
class CBattle_ShipUI_State
{
private:
	CBattle_Ship*	m_pMaster;
private:
	Graphics*		m_pGraphics;
	TextDX			m_dxFont;
private:
	Image* m_pDPBack;
	Image* m_pDPProgress;
	Image* m_pShipGuide;
	Image* m_pShipRank;
	std::string m_strDPProgressKey;
	std::string m_strShipRankKey;
	//===================================
	float m_maxDP;
	float m_currentDP;
	float m_maxWidth;
	float m_targetWidth;
	bool m_bAnimation;
	//===================================
	std::string m_strShipName;
public:
	CBattle_ShipUI_State();
	~CBattle_ShipUI_State();

	bool initialize(Graphics* g, CBattle_Ship* pMaster);
	void update(float frameTime);
	void render();

	//=============================================
	// Member Functions
	//=============================================
	
	void moveX(float distance);
	void moveY(float distance);
	
	void setupStateUIPos();

	void damageToDP(float damage);
	void updateAnimation();

	//=============================================
	// Member Functions
	//=============================================
	
	void setPlayerColorable(bool bPlayerColor)
	{
		if (bPlayerColor)
			m_dxFont.setFontColor(battleShipUIStateNS::FONT_PLAYER_COLOR);
		else
			m_dxFont.setFontColor(battleShipUIStateNS::FONT_ENEMY_COLOR);
	}
};

#endif // !_BATTLE_SHIPUI_STATE_H