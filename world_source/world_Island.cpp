#include "stdafx.h"
#include "world_Island.h"


void CWorld_Island::add_Child()
{
	//load data 가져오기
	//존재하지 않으면 초기화

	//add child island

	//CChild_Island* obj = new CChild_Island;
	//obj->initialize(MONEY, 100);	//money increase 100
	//child_node.emplace_back(_child);

	//switch (id)
	//{
	//case 0:
	//case 1:
	//case 2:
	//case 3:
	//case 4:
	//case 5:
	//case 6:
	//case 7:
	//case 8:
	//case 9:
	//case 10:
	//case 11:
	//case 12:
	//case 13:
	//case 14:
	//case 15:
	//case 16:
	//case 17:
	//default:
	//}
}

CWorld_Island::CWorld_Island()
{
}


CWorld_Island::~CWorld_Island()
{
}

void CWorld_Island::turn_end()
{
	if (c_turn > 0)
	{
		for (auto iter : child_node)
			iter->turn_end();

		for (auto iter : building_node)
			iter->turn_end();

		for (auto iter : current_ship)
			iter->turn_end();
	}
	c_turn++;
}

void CWorld_Island::initialize(Graphics* g, Input* i, std::string _name, UINT _id, UINT _x, UINT _y, UINT _width, UINT _height)
{
	m_pGraphics = g;
	m_pInput = i;

	name = _name;
	id = _id;
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	c_turn = 0;

	add_Child();
	//u_island = false;

	//printf("%s\t%d\t%d\t%d\t%d\t%d\t \n", name, id, x, y, width, height);
}

void CWorld_Island::render()
{
	m_pGraphics->spriteBegin();

	for (auto iter : show_ship)
		iter->render();

	m_pGraphics->spriteEnd();
}

void CWorld_Island::add_ship(CProduction_Ship * _ship)
{
	for (auto iter : show_ship)
		SAFE_DELETE(iter);
	show_ship.clear();

	current_ship.emplace_back(_ship);

	CWorld_Ship* obj;

	for (int i = 0; i < current_ship.size(); i += 5)
	{
		POINT rand_pt = { rand() % 100, rand() % 100 };	//-r ~ r

		obj = new CWorld_Ship;

		//obj->initialize(m_pGraphics, m_pInput, getName(), rand_pt.x, rand_pt.y, { getX(), getY() });
		obj->initialize(m_pGraphics, m_pInput, "SN_BC_Stalingrad_sd", rand_pt.x, rand_pt.y, { getX(), getY() });
		show_ship.emplace_back(obj);
	}
}

CBuilding * CWorld_Island::get_Building(int _index)
{
	int index = 0;

	for (auto iter : building_node)
	{
		if (index++ == _index)
			return iter;
	}
}
