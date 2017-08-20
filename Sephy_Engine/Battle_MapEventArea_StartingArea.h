#ifndef _BATTLE_MAP_EVENT_AREA_STARTING_H
#define _BATTLE_MAP_EVENT_AREA_STARTING_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_StartingArea;

#include "image.h"

namespace battleMapUIStartingAreaNS
{
	const std::string ERROR_MESSAGE = "Battle MapUI StartingArea Initialize Failed";

	const std::string STARTING_AREA_FILENAME_KEY	= "Flag";
	const std::string STARTING_AREA_FLAG_TYPE_A_KEY = "A_";
	const std::string STARTING_AREA_FLAG_TYPE_B_KEY = "B_";
	const std::string AREA_FLAG_SHADOW_KEY			= "FlagShadow_";
	const UINT STARTING_AREA_FLAG_MAX_FRAME			= 46; // 0 ~ 45	
	const float STARTING_AREA_RADIUS = 500.f;
	const float STARTING_AREA_SMOOTHNESS = 0.1f;
	const float CAPTURE_TIME = 120.f;
	//======================================================
	const std::string PROGRESS_BACK = "ProgressBack";
	const std::string PROGRESS_BLUE = "ProgressBlue";
	const std::string PROGRESS_RED = "ProgressRed";
	const float PROGRESS_WIDTH = 287.f;
	const float PROGRESS_RELATE_X = -(290.f / 2.f);
	const float PROGRESS_RELATE_Y = 30.f;
}


class CBattle_MapEventArea_StartingArea
{
private:
	Graphics* m_pGraphics;

private:
	Image* m_pAreaFlag;
	Image* m_pAreaFlagShadow;
	std::string m_strFlagKey;
	std::string m_strFlagShadowKey;
	int			m_nSpriteNumber;
	int			m_nAreaType;
	float		m_fAreaRadius;
	float		m_centerX, m_centerY;
	bool		m_bPlayerArea;
private:
	Image* m_pProgressback;
	Image* m_pProgress;
	bool m_bCapturing;
	bool m_bCaptureToPlayer;
	float m_fCaptureTime;
public:
	CBattle_MapEventArea_StartingArea();
	~CBattle_MapEventArea_StartingArea();

	bool initialize(Graphics* g, int nAreaType = 0);
	void update(float frameTime);
	void render();	

	//============================================
	// Member Functions
	//============================================

	void moveX(float fDistance);
	void moveY(float fDistance);

	void capturing(bool bPlayerTo);

	//============================================
	// Setter Functions
	//============================================

	void setFlagCenterX(float fCenterX);
	void setFlagCenterY(float fCenterY);

	void setPlayerArea(bool bPlayerArea)
	{
		m_bPlayerArea = bPlayerArea;
	}
	
	//============================================
	// Getter Functions
	//============================================
	float getCenterX() const
	{
		return m_centerX;
	}
	float getCenterY() const
	{
		return m_centerY;
	}
	float getRadius() const
	{
		return m_fAreaRadius;
	}

	bool isPlayerArea() const
	{
		return m_bPlayerArea;
	}
};

#endif // !_BATTLE_MAP_EVENT_AREA_STARTING_H