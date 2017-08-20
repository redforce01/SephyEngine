#include "stdafx.h"
#include "world_User.h"
#include "world_Scene.h"


CWorld_User::CWorld_User()
{
	is_update = true;

	for (int i = 0; i < world_userNS::MAX_BUILD; i++)
		current_building[i] = 0;
}


CWorld_User::~CWorld_User()
{
}

void CWorld_User::initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research)
{
	m_pGraphics = g;
	m_pInput = i;

	money = _money;
	iron = _iron;
	fuel = _fuel;
	research = _research;
}

void CWorld_User::add_ship(CProduction_Ship * _ship, CWorld_Island * _island)
{
	_ship->setIsland(_island->getID());
	_island->add_ship(_ship);
	ship_node.emplace_back(_ship);
}

void CWorld_User::add_resource(E_RESOURCE _type, int _resource)
{
	switch (_type)
	{
	case MONEY:
		money += _resource;
		break;
	case IRON:
		iron += _resource;
		break;
	case FUEL:
		fuel += _resource;
		break;
	case RESEARCH:
		research += _resource;
		break;
	}
}

void CWorld_User::remove_island(UINT _index)
{
	for (auto iter = island_node.begin(); iter != island_node.end(); iter++)
	{
		if ((*iter)->getID() == _index)
		{
			island_node.erase(iter);
			break;
		}
	}
}

void CWorld_User::print_world_log(const std::string message)
{
	scene->print_world_log(message);
}

std::deque<std::string> CWorld_User::get_log_message()
{
	return scene->get_log_message();;
}

int CWorld_User::get_resource(E_RESOURCE _type)
{
	switch (_type)
	{
	case MONEY:
		return money;
	case IRON:
		return iron;
	case FUEL:
		return fuel;
	case RESEARCH:
		return research;
	}
}

bool CWorld_User::spend_resource(E_RESOURCE _type, int _amount)
{
	switch (_type)
	{
	case MONEY:
		if (money - _amount >= 0)
		{
			money -= _amount;

			return true;
		}
		break;
	case IRON:
		if (iron - _amount >= 0)
		{
			iron -= _amount;

			return true;
		}
		break;
	case FUEL:
		if (fuel - _amount >= 0)
		{
			fuel -= _amount;

			return true;
		}
		break;
	case RESEARCH:
		if (research - _amount >= 0)
		{
			research -= _amount;

			return true;
		}
		break;
	}

	return false;
}
