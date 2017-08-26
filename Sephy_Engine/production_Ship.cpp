#include "stdafx.h"
#include "production_Ship.h"
#include "world_Ship.h"
#include "world_User.h"

CProduction_Ship::CProduction_Ship()
{
	is_create = false;
	is_complete = false;
	is_destroy = false;

	is_fuel = true;
	is_move = false;
}


CProduction_Ship::~CProduction_Ship()
{
	building.clear();
}

void CProduction_Ship::turn_end()
{
	if (is_destroy == true)
		return;

	if (start_turn == turn)
	{
		user->print_world_log("Create Start Ship : " + name);
		is_create = true;
	}

	if (turn == 1)
		user->print_world_log("Complete Ship : " + name);

	if (turn <= 1)
	{
		if (is_complete == true)
		{
			if (user->spend_resource(FUEL, fuel_cost))
			{
				is_fuel = true;
				is_move = false;
			}
			else
			{
				user->print_world_log("Ban Ship (Short fuel) : " + name);
				is_fuel = false;
				return;
			}
		}

		is_complete = true;

		user->add_decrease_resource(FUEL, fuel_cost);

		//자원 감소 및 자원 부족한거 체크
		//이번 턴 작동 여부 체크
	}

	turn--;
}

void CProduction_Ship::initialize(std::string _name, int _id, int _turn, int _money, int _iron, int _fuel, int _research, int _cost)
{
	name = _name;
	id = _id;
	start_turn = turn = _turn;
	money = _money;
	iron = _iron;
	fuel = _fuel;
	research = _research;
	fuel_cost = _cost;
}

void CProduction_Ship::release()
{
	building.clear();
}

void CProduction_Ship::load(bool _move, bool _fuel)
{
	is_move = _move;
	is_fuel = _fuel;
}

int CProduction_Ship::get_resource(int _type)
{
	switch (_type)
	{
	case 0:
		return money;
	case 1:
		return iron;
	case 2:
		return fuel;
	case 3:
		return research;
	}
}
