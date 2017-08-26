#include "stdafx.h"
#include "world_Island_Detail_UI.h"
#include "world_Island.h"

CWorld_Island_Detail_UI::CWorld_Island_Detail_UI()
{
	is_show = false;
}


CWorld_Island_Detail_UI::~CWorld_Island_Detail_UI()
{
	SAFE_DELETE(background);
}

void CWorld_Island_Detail_UI::initialize(Graphics * g, Input * i, CWorld_Island* _island)
{
	if (background == nullptr)
		background = new Image;

	money = 0;
	iron = 0;
	fuel = 0;
	research = 0;

	is_show = true;

	m_pGraphics = g;
	m_pInput = i;
	island = _island;

	background->initialize(
		m_pGraphics, world_island_detailNS::DETAIL_WIDTH,
		world_island_detailNS::DETAIL_HEIGHT, 0,
		IMAGEMANAGER->getTexture(world_island_detailNS::DETAIL_NAME)
	);
	background->setX(island->getX() - island->getWidth() / 2 - world_island_detailNS::DETAIL_WIDTH);
	background->setY(island->getY() - world_island_detailNS::DETAIL_HEIGHT / 2);

	rt_money = RectMake(
		background->getX() + world_island_detailNS::MARGIN,
		background->getY() + world_island_detailNS::MARGIN,
		world_island_detailNS::DETAIL_WIDTH - world_island_detailNS::MARGIN * 2,
		world_island_detailNS::FONT_HEIGHT
	);
	rt_iron = RectMake(
		rt_money.left, rt_money.bottom,
		world_island_detailNS::DETAIL_WIDTH - world_island_detailNS::MARGIN * 2,
		world_island_detailNS::FONT_HEIGHT
	);
	rt_fuel = RectMake(
		rt_iron.left, rt_iron.bottom,
		world_island_detailNS::DETAIL_WIDTH - world_island_detailNS::MARGIN * 2,
		world_island_detailNS::FONT_HEIGHT
	);
	rt_research = RectMake(
		rt_fuel.left, rt_fuel.bottom,
		world_island_detailNS::DETAIL_WIDTH - world_island_detailNS::MARGIN * 2,
		world_island_detailNS::FONT_HEIGHT
	);

	for (auto iter : island->get_child())
	{
		switch (iter->get_type())
		{
		case MONEY:
			money += iter->get_resource();
			break;
		case IRON:
			iron += iter->get_resource();
			break;
		case FUEL:
			fuel += iter->get_resource();
			break;
		case RESEARCH:
			research += iter->get_resource();
			break;
		}
	}

	for (int a = 0; a < island->get_Building_Size(); a++)
	{
		if (island->get_Building(a) == nullptr ||
			island->get_Building(a)->get_is_complete() == false)
			continue;

		money += island->get_Building(a)->get_produce_resource()[MONEY];
		iron += island->get_Building(a)->get_produce_resource()[IRON];
		fuel += island->get_Building(a)->get_produce_resource()[FUEL];
		research += island->get_Building(a)->get_produce_resource()[RESEARCH];
	}

	m_dxFont.initialize(g, world_island_detailNS::FONT_SIZE, false, false, world_island_detailNS::FONT);
}

void CWorld_Island_Detail_UI::update(float frameTime)
{
}

void CWorld_Island_Detail_UI::render()
{
	if (is_show == false)
		return;

	m_pGraphics->spriteBegin();

	background->draw();

	m_dxFont.print("money : ", rt_money, DT_LEFT + DT_VCENTER);
	m_dxFont.print(std::to_string(money), rt_money, DT_RIGHT + DT_VCENTER);
	m_dxFont.print("iron : ", rt_iron, DT_LEFT + DT_VCENTER);
	m_dxFont.print(std::to_string(iron), rt_iron, DT_RIGHT + DT_VCENTER);
	m_dxFont.print("fuel : ", rt_fuel, DT_LEFT + DT_VCENTER);
	m_dxFont.print(std::to_string(fuel), rt_fuel, DT_RIGHT + DT_VCENTER);
	m_dxFont.print("research : ", rt_research, DT_LEFT + DT_VCENTER);
	m_dxFont.print(std::to_string(research), rt_research, DT_RIGHT + DT_VCENTER);

	m_pGraphics->spriteEnd();
}

void CWorld_Island_Detail_UI::release()
{
	SAFE_DELETE(background);
}

void CWorld_Island_Detail_UI::w_move_ud(float _speed)
{
	background->moveY(_speed);

	rt_money.top += _speed;
	rt_money.bottom += _speed;
	rt_iron.top += _speed;
	rt_iron.bottom += _speed;
	rt_fuel.top += _speed;
	rt_fuel.bottom += _speed;
	rt_research.top += _speed;
	rt_research.bottom += _speed;
}

void CWorld_Island_Detail_UI::w_move_rl(float _speed)
{
	background->moveX(_speed);

	rt_money.left += _speed;
	rt_money.right += _speed;
	rt_iron.left += _speed;
	rt_iron.right += _speed;
	rt_fuel.left += _speed;
	rt_fuel.right += _speed;
	rt_research.left += _speed;
	rt_research.right += _speed;
}
