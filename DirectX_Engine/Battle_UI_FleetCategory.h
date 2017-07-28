#ifndef _BATTLE_UI_FLEETCATEGORY_H
#define _BATTLE_UI_FLEETCATEGORY_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetCategory;

#include "image.h"
#include "systemButton.h"

namespace battleUIFleetCategoryNS
{
	const std::string CATEGORY_SHIP_BUTTON_NAME = "CatagoryShip";
	const UINT CATEGORY_SHIP_BUTTON_X = 50;
	const UINT CATEGORY_SHIP_BUTTON_Y = 30;
}

struct tagBattleFleetItem
{
	Image*		shipImage;
	std::string shipName;
	int			shipCount;
};

class CBattle_UI_FleetCategory
{
	typedef std::vector<tagBattleFleetItem*> FleetList;
private:
	FleetList m_vFleetList;
	
private:
	bool m_bVisibleFleetList;

private:
	SystemButton* m_pCategoryButton;

public:
	CBattle_UI_FleetCategory();
	~CBattle_UI_FleetCategory();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

public:
	//=====================================================
	// Member Functions
	//=====================================================

	void onShowFleetList();
	


	void addFleetItem(tagBattleFleetItem* pItem)
	{
		m_vFleetList.emplace_back(pItem);
	}

	
	//=====================================================
	// Getter Functions
	//=====================================================
	
	FleetList getFleetList() const
	{
		return m_vFleetList;
	}
};

#endif // !_BATTLE_UI_FLEETCATEGORY_H