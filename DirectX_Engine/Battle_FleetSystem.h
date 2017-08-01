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

enum BATTLE_FLEET_LIST
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
	std::vector<CBattle_Ship*> ships;
	BATTLE_FLEET_LIST enFleetType;
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

	void addFleet(tagFleetData* fleet)
	{
		for (auto iter : m_vFleets)
		{
			if (iter->enFleetType == fleet->enFleetType)
			{
				iter = fleet;
				break;
			}			
		}

		m_vFleets.emplace_back(fleet);
	}
};

#endif // !_BATTLE_FLEETSYSTEM_H
