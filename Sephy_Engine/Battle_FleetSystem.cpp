#include "stdafx.h"
#include "Battle_FleetSystem.h"


CBattle_FleetSystem::CBattle_FleetSystem()
{
}


CBattle_FleetSystem::~CBattle_FleetSystem()
{
}

bool CBattle_FleetSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		for (int i = 0; i < battleFleetSystemNS::FLEET_TOTAL_SIZE; i++)
		{
			tagFleetData* tempFleet = new tagFleetData;
			tempFleet->enFleetType = (BATTLE_FLEET_LIST)(i);
			m_vFleets.emplace_back(tempFleet);
		}
		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFleetSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_FleetSystem::update(float frameTime)
{

}

void CBattle_FleetSystem::render()
{

}