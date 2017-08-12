#ifndef _BATTLE_UI_DESTINATION_H
#define _BATTLE_UI_DESTINATION_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_Destination;
	
#include "image.h"

namespace battleUIDestinationNS
{
	const std::string DESTINATION_GREEN_NAME = "Destination";
	const std::string DESTINATION_BLUE_NAME = "DestinationBlue_Our_";
	const std::string DESTINATION_YELLOW_NAME = "DestinationYellow_Order_";
	const UINT DESTINATION_MAX = 35;
	const float DESTINATION_VIEW_TIME = 2.f;
	const std::string ERROR_MESSAGE = "Destination Initialize Failed";
}

enum class DESTINATION_TYPE
{ DESTINATION_GREEN, DESTINATION_BLUE, DESTINATION_YELLOW, };

class CBattle_UI_Destination
{
private:
	Graphics*			m_pGraphics;
	std::string			m_strSpriteKey;
	Image*				m_pDestinationGreen;
	Image*				m_pDestinationBlue;
	Image*				m_pDestinationYellow;
	std::string			m_strGreenKey;
	std::string			m_strBlueKey;
	std::string			m_strYellowKey;
	int					m_nCurrentSprite;
	int					m_nSpriteMax;
	float				m_fChangeTime;
	float				m_fChangeDeltaTime;
	bool				m_bActive;
	bool				m_bInitialized;
	DESTINATION_TYPE	m_enDestinationType;
public:
	CBattle_UI_Destination();
	~CBattle_UI_Destination();

	bool initialize(Graphics* g);
	void update(float frameTime);
	void render();

	//============================================
	// Member Functions
	//============================================

	void updateDestination(float frameTime);
	void changeDestination();

	void moveX(float distance);
	void moveY(float distance);
	
	//============================================
	// Setter Functions
	//============================================
	void setActive(bool bActive)
	{
		m_bActive = bActive;
		m_nCurrentSprite = 0;
		m_enDestinationType = DESTINATION_TYPE::DESTINATION_GREEN;
	}

	void setDestinationPos(VECTOR2 v);

	//============================================
	// Getter Functions
	//============================================

	VECTOR2 getDestinationPos() const
	{
		return VECTOR2(m_pDestinationGreen->getCenterX(), m_pDestinationGreen->getCenterY());
	}
};

#endif // !_BATTLE_UI_DESTINATION_H
