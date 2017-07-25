#include "stdafx.h"
#include "world_Action_Ship.h"


CWorld_Action_Ship::CWorld_Action_Ship()
{
}


CWorld_Action_Ship::~CWorld_Action_Ship()
{
}

bool CWorld_Action_Ship::initialize(Graphics* g, Input* i)
{
	m_pGraphics = g;
	m_pInput = i;

	return true;
}

void CWorld_Action_Ship::update(float frameTime)
{
	//if (current_ship.size() > 0)
	//{
	//	if (m_pInput->getMouseLButton())
	//	{
	//		유닛 선택 후 이동
	//	}
	//}
	//else
	//{

	//}
	for (auto iter : w_ship)
		iter->update(frameTime);
}

void CWorld_Action_Ship::render()
{
	for (auto iter : w_ship)
		iter->render();
}

void CWorld_Action_Ship::add_ship(std::string _name, UINT _x, UINT _y, float _degree)
{
	CWorld_Ship* obj = new CWorld_Ship;

	obj->initialize(m_pGraphics, m_pInput, _name, _x, _y, _degree);

	w_ship.emplace_back(obj);
	current_ship.emplace_back(obj);
}
