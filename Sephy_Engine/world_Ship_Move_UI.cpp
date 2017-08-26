#include "stdafx.h"
#include "world_Ship_Move_UI.h"
#include "world_ShipList_UI.h"
#include "world_Player.h"
#include "world_Scene.h"

void CWorld_Ship_Move_UI::click_event(CWorld_Island* _island)
{
	if (player->get_cur_ship().size() <= 0)
		return;

	int count = 0;

	CWorld_CG* cg = new CWorld_CG;
	
	cg->SetLoadLinkUser(player);

	cg->initialize(m_pGraphics, m_pInput);
	
	cg->create_move_ship_cg(player->get_select_island()->getPt(), _island->getPt(), _island->getID());

	player->get_scene()->add_CG(cg);
	player->get_select_island()->remove_ship_img();

	for (auto iter : player->get_cur_ship())
		iter->set_is_move(true);
}

CWorld_Ship_Move_UI::CWorld_Ship_Move_UI()
{
	mouse_up = false;
}

CWorld_Ship_Move_UI::~CWorld_Ship_Move_UI()
{
	can_island.clear();
}

void CWorld_Ship_Move_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;
}

void CWorld_Ship_Move_UI::update(float frameTime)
{
	if (m_pInput->getMouseRButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			for (auto iter : can_island)
			{
				if (PtInRect(&iter->getRect(), m_pInput->getMousePt()))
				{
					click_event(iter);

					list_ui->delete_move();
				}
			}
		}

		mouse_up = false;
	}
}

void CWorld_Ship_Move_UI::render()
{
	for (auto iter : can_island)
		m_pGraphics->drawRect(iter->getRect());
}
