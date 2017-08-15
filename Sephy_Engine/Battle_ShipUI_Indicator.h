#ifndef _BATTLE_SHIPUI_INDICATOR_H
#define _BATTLE_SHIPUI_INDICATOR_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipUI_Indicator;

#include "image.h"

namespace battleShipUIIndicatorNS
{
	const std::string INDICATOR_FILENAME	= "Indicators";
	const std::string INDICATOR_NORMAL_KEY	= "Normal_";
	const std::string INDICATOR_OVERLAB_KEY = "Normal_";
	const std::string INDICATOR_CLICK_KEY	= "Normal_";
	//const std::string INDICATOR_OVERLAB_KEY = "Mouse_"; // ORIGINAL INDICATOR - NOT USING
	//const std::string INDICATOR_CLICK_KEY	= "Click_"; // ORIGINAL INDICATOR - NOT USING
	const std::string INDICATOR_BLUE_KEY	= "B";
	const std::string INDICATOR_GREEN_KEY	= "G";
	const UINT INDICATOR_MAX_FRAME = 5; // size 5 ( 0 ~ 4 )
	
	const float INDICATOR_RELATE_MARGIN = 5;
}

enum class INDICATOR_TYPE
{ INDICATOR_BLUE, INDICATOR_GREEN };

class CBattle_Ship;
class CBattle_ShipUI_Indicator : public Image
{
private:
	Graphics*		m_pGraphics;
	Input*			m_pInput;
private:
	std::string		m_strIndicatorKey;
	std::string		m_strIndicatorTypeKey;
	INDICATOR_TYPE	m_enIndicatorType;
	int				m_nSpriteNumber;
	RECT			m_rcIndicator;
	CBattle_Ship*	m_pMaster;
public:
	CBattle_ShipUI_Indicator();
	~CBattle_ShipUI_Indicator();

	bool initialize(Graphics* g, Input* i, INDICATOR_TYPE type, CBattle_Ship* pMaster);
	void update(float frameTime);
	void render();

	//==============================================
	// Member Functions
	//==============================================

	void moveX(float distance);
	void moveY(float distance);

	void updateSprite();
	void setUIPos();

	//==============================================
	// Setter Functions
	//==============================================

	void setIndicatorType(INDICATOR_TYPE type)
	{
		m_enIndicatorType = type;
	}
};

#endif // !_BATTLE_SHIPUI_INDICATOR_H
