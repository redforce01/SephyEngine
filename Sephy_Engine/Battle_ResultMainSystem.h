#ifndef _BATTLE_RESULT_MAIN_SYSTEM_H
#define _BATTLE_RESULT_MAIN_SYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ResultMainSystem;

#include "systemBase.h"
#include "systemButton.h"
#include "Battle_ResultSystem.h"
#include "Battle_ResultPlayerView.h"
#include "Battle_ResultEnemyView.h"

namespace battleResultMainSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Result Main System Initialize Failed";
	const std::string LOADING_BLACK_BACKGROUND = "1080p_WHITE";
	const COLOR_ARGB LOADING_BLACK_BACK_COLOR_FILTER = SETCOLOR_ARGB(255, 1, 1, 1);
	const std::string BATTLE_RESULT_BACKGROUND_KEY = "Battle_Result_Background";
	const std::string BATTLE_RESULT_BACKGROUND_0 = "Battle_Result_Background0";
	const std::string BATTLE_RESULT_BACKGROUND_1 = "Battle_Result_Background1";
	const std::string BATTLE_RESULT_BACKGROUND_2 = "Battle_Result_Background2";
	const float BATTLE_RESULT_BACKGROUND_CHANGE_TIME = 7.0f;
	const float BATTLE_BACKGROUND_TYPE_A_WIDTH = 800;
	const float BATTLE_BACKGROUND_TYPE_A_HEIGHT = 501;
	const float BATTLE_BACKGROUND_TYPE_B_WIDTH = 1024;
	const float BATTLE_BACKGROUND_TYPE_B_HEIGHT = 768;
	//=====================================================================
	const std::string RESULT_PANEL_TEXT = "ResultPanelText";
	const std::string RESULT_PANEL_TEXT_SHADOW = "ResultPanelTextSh";
	const COLOR_ARGB RESULT_PANEL_SHADOW_COLOR_FILTER = D3DCOLOR_ARGB(64, 64, 64, 64);
	const float RESULT_PANEL_RELATE_X = 100;
	const float RESULT_PANEL_RELATE_Y = 100;
	//=====================================================================
	const std::string OK_BUTTON_NAME = "OK";
	const float OK_BUTTON_RELATE_X = -200; // (g_fScreenWidth - 100)
	const float OK_BUTTON_RELATE_Y = -100; // (g_fScreenHeight - 100)
}

class CBattle_ResultMainSystem : public SystemBase
{
private:
	CBattle_ResultSystem* m_pResultSystem;
	CBattle_ResultPlayerView* m_pResultPlayerView;
	CBattle_ResultEnemyView* m_pResultEnemyView;
private:
	Image*	m_pBlackBack;
	Image*	m_pResultBackground;
	float	m_fBackgroundTime;
	float	m_fAlphaValue;
	bool	m_bChangeImage;
	bool	m_bBackVisible;

	Image* m_pResultPanelText;
	Image* m_pResultPanelTextShadow;
	SystemButton* m_pOKButton;
	std::vector<std::string> m_vRemainPlayerShips;
	std::vector<std::string> m_vRemainComputerShips;
private:

public:
	CBattle_ResultMainSystem();
	~CBattle_ResultMainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	static void functionOKButton();
};

#endif // !_BATTLE_RESULT_MAIN_SYSTEM_H
