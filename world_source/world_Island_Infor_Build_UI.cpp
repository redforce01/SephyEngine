#include "stdafx.h"
#include "world_Island_Infor_Build_UI.h"
#include "world_Player.h"
#include "World_Island_Data.h"
#include "World_Island_Infor_UI.h"

void CWorld_Island_Infor_Build_UI::rect_initialize(RECT _rt)
{
	for (int i = 0; i < world_island_infor_buildNS::MAX_BOX; i++)
	{
		if (i >= world_island_infor_buildNS::MAX_BOX / 2)
		{
			rt_box[i] = rt_box[i - world_island_infor_buildNS::MAX_BOX / 2];
			rt_box[i].top = rt_box[i - world_island_infor_buildNS::MAX_BOX / 2].top + world_island_infor_buildNS::BOX_HEIGHT + world_island_infor_buildNS::MARGIN / 2;
			rt_box[i].bottom = rt_box[i - world_island_infor_buildNS::MAX_BOX / 2].bottom + world_island_infor_buildNS::BOX_HEIGHT + world_island_infor_buildNS::MARGIN / 2;

			continue;
		}

		rt_box[i] = RectMake(
			_rt.left + world_island_infor_buildNS::MARGIN + (world_island_infor_buildNS::BOX_WIDTH + world_island_infor_buildNS::MARGIN / 2) * i,
			_rt.top + world_island_infor_buildNS::MARGIN, world_island_infor_buildNS::BOX_WIDTH, world_island_infor_buildNS::BOX_HEIGHT
		);
	}
}

bool CWorld_Island_Infor_Build_UI::is_build(CBuilding * _building)
{
	if (player->get_cur_building(_building->get_building()) > 0)
		return true;

	return false;
}

CWorld_Island_Infor_Build_UI::CWorld_Island_Infor_Build_UI()
{
	for (int i = 0; i < world_island_infor_buildNS::MAX_BOX; i++)
		rt_box[i] = { 0, };

	mouse_up = false;

	buy_infor = new CWorld_Building_Buy_Infor;
}


CWorld_Island_Infor_Build_UI::~CWorld_Island_Infor_Build_UI()
{
}

void CWorld_Island_Infor_Build_UI::initialize(Graphics * g, Input * i, UINT _index, RECT _rt)
{
	m_pGraphics = g;
	m_pInput = i;
	index = _index;

	rect_initialize(_rt);

	buy_infor->initialize(g, i);

	m_dxFont.initialize(g, world_island_infor_buildNS::FONT_SIZE, true, false, world_island_infor_buildNS::FONT);
}

void CWorld_Island_Infor_Build_UI::update(float frameTime)
{

	for (int i = 0; i < player->get_data()->get_Building_Size(); i++)
	{
		if (m_pInput->getMouseLButton())
			mouse_up = true;
		else
		{
			if (mouse_up == true)
			{
				if (i == 0)	//Command Center
					continue;

				//if (PtInRect(&rt_box[i], m_pInput->getMousePt()) && is_build(player->get_data()->get_Building()[i]) == true)
				if (PtInRect(&rt_box[i - 1], m_pInput->getMousePt()) && is_build(player->get_data()->get_Building()[i]) == true)
					infor_ui->set_building(index, player->get_data()->get_Building()[i]);
			}
			if (i == player->get_data()->get_Building_Size() - 1)
				mouse_up = false;
		}
	}

	for (int i = 0; i < player->get_data()->get_Building_Size(); i++)
	{
		if (i == 0)	//Command Center
			continue;

		//if (PtInRect(&rt_box[i], m_pInput->getMousePt()) && is_build(player->get_data()->get_Building()[i]) == true)
		if (PtInRect(&rt_box[i - 1], m_pInput->getMousePt()) && is_build(player->get_data()->get_Building()[i]) == true)
		{
			buy_infor->set_building(player->get_data()->get_Building()[i]);
			break;
		}
		else buy_infor->set_building(nullptr);
	}

	buy_infor->update(frameTime);

}

void CWorld_Island_Infor_Build_UI::render()
{
	m_pGraphics->spriteBegin();

	for (int i = 0; i < player->get_data()->get_Building_Size(); i++)
	{
		if (i == 0)	//Command Center
			continue;

		if (is_build(player->get_data()->get_Building()[i]) == true)
			m_dxFont.print(player->get_data()->get_Building()[i]->getName(), rt_box[i - 1], DT_CENTER + DT_VCENTER);
			//m_dxFont.print(player->get_data()->get_Building()[i]->getName(), rt_box[i], DT_CENTER + DT_VCENTER);
	}

	m_pGraphics->spriteEnd();

	for (int i = 0; i < world_island_infor_buildNS::MAX_BOX; i++)
		m_pGraphics->drawRect(rt_box[i]);

	buy_infor->render();
}
