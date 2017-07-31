#ifndef _BATTLE_UI_FLEETMARK_H
#define _BATTLE_UI_FLEETMARK_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetMark;

#include "image.h"
#include <vector>
#include <string>

namespace battleFleetMarkNS
{
	const std::string ERROR_MESSAGE = "Fleet Mark Initialize Failed";
	const std::string FLEET_MARK_FILENAME = "Fleet_Mark_";
	const std::string FLEET_TEXT_FILENAME = "Fleet_Text_";
	const UINT FLEET_MARK_MAX_COUNT = 8;
	const UINT FLEET_MARK_X = 0.f;
	const UINT FLEET_MARK_Y = 300.f;
	const UINT FLEET_MARK_MARGIN = 3;
	const UINT FLEET_MARK_TOTAL_WIDTH = 110;
	const UINT FLEET_MARK_TOTAL_HEIGHT = 30;
}

class CBattle_UI_FleetMark
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
private:
	Image*		m_pFleetMark;
	Image*		m_pFleetText;
	std::string m_strFleetMarkKey;
	std::string m_strFleetTextKey;
	int			m_nIndex;
	float		m_x, m_y;
	float		m_width, m_height;
	RECT		m_rcFleetMark;
	bool		m_bActive;
private:	
	std::vector<int> m_vShipIndex;
	

public:
	CBattle_UI_FleetMark();
	~CBattle_UI_FleetMark();

	bool initialize(Graphics* g, Input* i, int index);
	void update(float frameTime);
	void render();

	void setActive(bool bActive)
	{
		m_bActive = bActive;
	}

	void addShipToFleet(int shipNumber)
	{
		m_vShipIndex.emplace_back(shipNumber);
	}

	bool getActive() const
	{
		return m_bActive;
	}
};

#endif // !_BATTLE_UI_FLEETMARK_H
