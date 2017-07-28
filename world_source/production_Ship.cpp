#include "stdafx.h"
#include "production_Ship.h"
#include "world_Ship.h"

CProduction_Ship::CProduction_Ship()
{
}


CProduction_Ship::~CProduction_Ship()
{
}

void CProduction_Ship::turn_end()
{
}

void CProduction_Ship::initialize(std::string _name, UINT _id, UINT _money, UINT _iron, UINT _fuel, UINT _research, UINT _cost)
{
	name = _name;
	id = _id;
	money = _money;
	iron = _iron;
	fuel = _fuel;
	research = _research;
	fuel_cost = _cost;
}
