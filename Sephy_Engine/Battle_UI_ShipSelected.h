#ifndef _BATTLE_UI_SHIPSELECTED_H
#define _BATTLE_UI_SHIPSELECTED_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_ShipSelected;


#include "image.h"

namespace battleUIShipSelectedNS
{
	const std::string ERROR_MESSAGE = "Ship Selected UI Initialize Failed";
	const std::string SHIP_SELECTED_FILENAME = "IndicatorGreenSmall_";
	const float SHIP_SELECTED_SCALE = 0.75f;
	const UINT SHIP_SELECTED_MAX_FRAME = 36;
}

class CBattle_UI_ShipSelected : public Image
{
private:
	Graphics* m_pGraphics;
private:
	std::string m_strSelectedKey;
	int m_nSpriteNum;
	bool m_bActive;
public:
	CBattle_UI_ShipSelected();
	~CBattle_UI_ShipSelected();

	bool initialize(Graphics* g);
	void update(float frameTime);
	void render();

	void setActive(bool bActive)
	{
		m_bActive = bActive;
	}

	void setUIPosX(float objCenterX)
	{
		Image::setX(objCenterX - (spriteData.width / 2));
	}
	void setUIPosY(float objCenterY)
	{
		Image::setY(objCenterY - (spriteData.height / 2));
	}
};

#endif // !_BATTLE_UI_SHIPSELECTED_H
