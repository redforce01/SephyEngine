#include "stdafx.h"
#include "building.h"

CBuilding::CBuilding()
{
}


CBuilding::~CBuilding()
{
}

void CBuilding::turn_end()
{
	turn--;

	if (turn == 0)
	{
		//건물 완성
	}
	else if (turn < 0)
	{
		//사용 가능 및 자원 생산
		//배 생산
	}
}

void CBuilding::initialize(std::string _name, UINT _id, UINT _turn, UINT _nBuilding, UINT _nMoney, UINT _nIron, UINT _pMoney, UINT _pIron, UINT _pFuel, UINT _pResearch)
{
	name = _name;
	id = _id;
	turn = _turn;
	n_building = _nBuilding;
	
	need_resource[MONEY] = _nMoney;
	need_resource[IRON] = _nIron;

	produce_resource[MONEY] = _pMoney;
	produce_resource[IRON] = _pIron;
	produce_resource[FUEL] = _pFuel;
	produce_resource[RESEARCH] = _pResearch;

	//std::cout << "=================================" << std::endl;
	//std::cout << "Name : " << name << std::endl;
	//std::cout << "ID : " << id << std::endl;
	//std::cout << "Turn : " << turn << std::endl;
	//std::cout << "=================================" << std::endl;
	
	//printf("%s\t\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t \n", name, id, turn, n_building, need_resource[MONEY], need_resource[IRON], 
	//	produce_resource[MONEY], produce_resource[IRON], produce_resource[FUEL], produce_resource[RESEARCH]);
}

