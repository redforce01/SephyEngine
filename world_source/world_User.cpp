#include "stdafx.h"
#include "world_User.h"


CWorld_User::CWorld_User()
{
}


CWorld_User::~CWorld_User()
{
}

void CWorld_User::initialize(Graphics* g, Input* i, UINT _money, UINT _iron, UINT _fuel, UINT _research)
{
	m_pGraphics = g;
	m_pInput = i;

	money = _money;
	iron = _iron;
	fuel = _fuel;
	research = _research;
}

void CWorld_User::save_data(std::string p_c)	//player & computer
{
	//BEGIN p_c
	for (auto iter : island_node)
	{
		for (auto cIter : iter->get_child())
		{
			//이거 세이브 형식으로 저장
			cIter->get_type();
			cIter->get_resource();
		}

		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			//이거 세이브 형식으로 저장
			iter->get_Building(i)->getID();
		}

		for (auto sIter : ship_node)
		{
			//이거 세이브 형식으로 저장
			sIter->getID();
			sIter->getIsland();
			sIter->getX();
			sIter->getY();
		}
	}
}
