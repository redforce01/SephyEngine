#pragma once
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
}


class CBattle_MapUI_StartingArea
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
public:
	CBattle_MapUI_StartingArea();
	~CBattle_MapUI_StartingArea();

	bool initialize(Graphics* g, int nAreaType = 0);
	void update(float frameTime);
	void render();	

	//============================================
	// Member Functions
	//============================================

	void moveX(float fDistance);
	void moveY(float fDistance);

	//============================================
	// Setter Functions
	//============================================

	void setFlagCenterX(float fCenterX);
	void setFlagCenterY(float fCenterY);

	
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
};

