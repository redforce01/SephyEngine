#ifndef _BATTLE_SHIPUI_INDICATOR_H
#define _BATTLE_SHIPUI_INDICATOR_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipUI_Indicator;

#include "image.h"

namespace battleShipUIIndicatorNS
{
	const std::string INDICATOR_FILENAME	= "Indicators";
	const std::string INDICATOR_NORMAL_KEY	= "Normal_";
	const std::string INDICATOR_OVERLAB_KEY = "Mouse_";
	const std::string INDICATOR_CLICK_KEY	= "Click_";
	const std::string INDICATOR_BLUE_KEY	= "B";
	const std::string INDICATOR_GREEN_KEY	= "G";
	const UINT INDICATOR_MAX_FRAME = 5; // size 5 ( 0 ~ 4 )
	
	//IndicatorsBClick_
	//IndicatorsBMouse_
	//IndicatorsBNormal_
	//IndicatorsGClick
	//IndicatorsGMouse_
	//IndicatorsGNormal_
}

enum class INDICATOR_TYPE
{ INDICATOR_BLUE, INDICATOR_GREEN };

class CBattle_Ship;
class CBattle_ShipUI_Indicator : public Image
{
private:
	Input*			m_pInput;
	std::string		m_strIndicatorKey;
	std::string		m_strIndicatorTypeKey;
	INDICATOR_TYPE	m_enIndicatorType;
	int				m_nSpriteNumber;
	RECT			m_rcIndicator;
	CBattle_Ship*	m_pMaster;
public:
	CBattle_ShipUI_Indicator();
	~CBattle_ShipUI_Indicator();

	bool initialize(Graphics* g, Input* i, INDICATOR_TYPE type);
	void update(float frameTime);
	void draw();


	//==============================================
	// Setter Functions
	//==============================================

	void setIndicatorType(INDICATOR_TYPE type)
	{
		m_enIndicatorType = type;
	}
};

#endif // !_BATTLE_SHIPUI_INDICATOR_H
