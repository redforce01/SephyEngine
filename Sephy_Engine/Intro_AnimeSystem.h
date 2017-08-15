#ifndef _INTRO_ANIMESYSTEM_H
#define _INTRO_ANIMESYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CIntro_AnimeSystem;

#include "systemBase.h"

namespace introAnimeSystemNS
{
	const std::string ERROR_MESSAGE = "Intro Anime System Initialize Failed";
	const std::string OPENING_PLANE_KEY_NAME = "op¹ð±â";
	const std::string OPENING_PLANE_SH_KEY_NAME = "op¹ð±â¸ÖÆ¼±×¸²ÀÚ";
	const UINT OPENING_PLANE_MAX_FRAME = 201;
	const float OPENING_PLANE_WIDTH = 800;
	const float OPENING_PLANE_HEIGHT = 600;
	const COLOR_ARGB OPENING_PLANE_SHADOW_COLOR_FILTER = SETCOLOR_ARGB(32, 16, 16, 16);
	const float OPENING_PLANE_ANIMETIME = 0.01f;
	//==================================================================
	const std::string BLACK_MASKING_FILENAME = "1080p_WHITE";
	const COLOR_ARGB BLACK_MASKING_COLOR_FILTER = SETCOLOR_ARGB(255, 16, 16, 16);
	//==================================================================
	const std::string PANEL_FRONT_FILENAME = "Login";
	const std::string PANEL_SHADOW_FILENAME = "LoginSh";
	const UINT PANEL_WIDTH = 1024;
	const UINT PANEL_HEIGHT = 768;
	const std::string PANEL_SHIP_FILENAME = "Ship-USA-Missouri";
	const std::string PANEL_SHIP_SHADOW_FILENAME = "Ship-USA-MissouriSh";
	const COLOR_ARGB PANEL_SHADOW_COLOR_FILTER = SETCOLOR_ARGB(32, 16, 16, 16);
	const float PANEL_SHIP_RELATE_X = 15;
	const float PANEL_SHIP_RELATE_Y = -195.f;
	//==================================================================
	const std::string BACKGROUND_FILENAME = "Intro_background";
	const std::string BACKGROUND_MUSIC_FILENAME = "main_theme";
}

class CIntro_AnimeSystem : public SystemBase
{
private:
	Image* m_pOpeningPlane;
	Image* m_pOpeningPlaneShadow;
	int m_nCurrentFrame;
	std::string m_strOpeningPlaneKey;
	std::string m_strOpeningPlaneShadowKey;
	float m_startX; 
	float m_startY;
	float m_animeTime;
	bool m_bAnimeComplete;
private:
	Image* m_pBlackMasking;
	Image* m_pPanel;
	Image* m_pPanelShadow;
	Image* m_pPanelShip;
	Image* m_pPanelShipShadow;
	Image* m_pBackground;
public:
	CIntro_AnimeSystem();
	~CIntro_AnimeSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_INTRO_ANIMESYSTEM_H
