#ifndef _BATTLE_FLEETSYSTEM_H
#define _BATTLE_FLEETSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CBattle_FleetSystem;

#include <vector>
#include <functional>
#include "systemBase.h"
#include "Battle_Ship.h"

namespace battleFleetSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Fleet System Initialize Failed";	
	const std::string FLEET_ALPHA	= "ALPHA";
	const std::string FLEET_BRAVO	= "BRAVO";
	const std::string FLEET_CHARLIE = "CHARLIE";
	const std::string FLEET_DELTA	= "DELTA";
	const std::string FLEET_ECHO	= "ECHO";
	const std::string FLEET_FOXTROT = "FOXTROT";
	const std::string FLEET_GOLF	= "GOLF";
	const std::string FLEET_HOTEL	= "HOTEL";
	const UINT FLEET_TOTAL_SIZE = 8;
}

enum class BATTLE_FLEET_LIST
{
	FLEET_ALPHA = 0
	,FLEET_BRAVO
	,FLEET_CHARLIE
	,FLEET_DELTA
	,FLEET_ECHO
	,FLEET_FOXTROT
	,FLEET_GOLF
	,FLEET_HOTEL
};

struct tagFleetData
{
	bool						bActiveFleet;
	bool						bBufEffect;
	std::vector<CBattle_Ship*>	ships;
	CBattle_Ship*				flagShip;
	BATTLE_FLEET_LIST			enFleetType;

	tagFleetData()
	{
		bActiveFleet = false;
		bBufEffect = false;
		enFleetType = BATTLE_FLEET_LIST::FLEET_ALPHA;
	}
};

class CBattle_FleetSystem : public SystemBase
{	
private:
	std::vector<tagFleetData*> m_vFleets;
	std::vector<std::function<void()>> m_vFleetEffects;
public:
	CBattle_FleetSystem();
	~CBattle_FleetSystem();

	bool initialize(Game* gamePtr) override;
	void update(float frameTime) override;
	void render() override;

	void setFlagShip(CBattle_Ship* pShip, int fleetNumber)
	{
		for (auto iter : m_vFleets)
		{
			if (iter->flagShip == nullptr)
				continue;

			if (iter->flagShip->getShipUniqueID() != pShip->getShipUniqueID())
				continue;

			iter->bActiveFleet = false;
			iter->ships.clear();
			break;
		}

		m_vFleets[fleetNumber]->bActiveFleet = true;
		m_vFleets[fleetNumber]->flagShip = pShip;
	}

	void setFleetShips(std::vector<CBattle_Ship*> vFleetShips, int fleetNumber)
	{
		m_vFleets[fleetNumber]->ships = vFleetShips;
	}

	tagFleetData* getFleet(int fleetNum)
	{
		if (fleetNum < m_vFleets.size())
			return m_vFleets[fleetNum];
		else
			return nullptr;
	}
};

#endif // !_BATTLE_FLEETSYSTEM_H
