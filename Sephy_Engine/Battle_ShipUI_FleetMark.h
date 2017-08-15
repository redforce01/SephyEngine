#ifndef _BATTLE_SHIPUI_FLEETMARK_H
#define _BATTLE_SHIPUI_FLEETMARK_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipUI_FleetMark;

#include "image.h"

namespace battleShipUIFleetMarkNS
{
	const float FLEET_MARK_WIDTH = 20;
	const float FLEET_MARK_HEIGHT = 20;
	const float FLEET_MARK_POS_X = -20;
	const float FLEET_MARK_POS_Y = -10;

	const std::string FLEET_MARK_KEY = "Fleet_Mark_";
	const std::string FLEET_MARK_NONE = "Fleet_Mark_9";
}

class CBattle_Ship;
class CBattle_ShipUI_FleetMark : public Image
{
private:
	std::string		m_strFleetMarkKey;
	float			m_x, m_y;
	float			m_width, m_height;
	CBattle_Ship*	m_pMaster;
	
public:
	CBattle_ShipUI_FleetMark();
	~CBattle_ShipUI_FleetMark();

	bool initialize(Graphics* g);
	void update(float frameTime);
	void draw();

	//==========================================
	// Member Functions
	//==========================================

	void moveX(float distance);
	void moveY(float distance);

	void setUIPos();

	//==========================================
	// Setter Functions
	//==========================================

	void setMaster(CBattle_Ship* pShip);

	void setFleetMarkNumber(int nMark)
	{
		m_strFleetMarkKey = battleShipUIFleetMarkNS::FLEET_MARK_KEY + std::to_string(nMark);
		Image::setTextureManager(IMAGEMANAGER->getTexture(m_strFleetMarkKey));
	}
};

#endif // !_BATTLE_SHIPUI_FLEETMARK_H
