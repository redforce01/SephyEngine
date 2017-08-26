#include "stdafx.h"
#include "world_Player_Island_UI.h"
#include "world_Player.h"
#include "world_Scene_UI.h"

CWorld_Player_Island_UI::CWorld_Player_Island_UI()
{
}


CWorld_Player_Island_UI::~CWorld_Player_Island_UI()
{
}

void CWorld_Player_Island_UI::release()
{
	SAFE_DELETE(ship_list);
	SAFE_DELETE(island_infor);
}

bool CWorld_Player_Island_UI::initialize(Graphics * g, Input * i)
{
	ship_list = nullptr;
	island_infor = nullptr;

	is_show = false;

	m_pGraphics = g;
	m_pInput = i;
	
	return true;
}

void CWorld_Player_Island_UI::update(float frameTime)
{
	if (is_show == false)
		return;

	scene_ui->set_is_update(true);

	if (island_infor->get_show() == false)
	{
		ship_list->update(frameTime);
		scene_ui->set_is_update(false);
	}

	if (ship_list->get_show() == false)
	{
		island_infor->update(frameTime);
		scene_ui->set_is_update(false);
	}
}

void CWorld_Player_Island_UI::render()
{
	if (is_show == false)
		return;

	if (island_infor->get_show() == false)
		ship_list->render();

	if (ship_list->get_show() == false)
		island_infor->render();
}

//**********	show button ship list & island infor ui		**********//
void CWorld_Player_Island_UI::show_UI(POINT _pt, int _width, int _height)
{
	if (is_show == true)
		return;

	is_show = true;

	ship_list = new CWorld_PlayerUI_ShipList;
	island_infor = new CWorld_PlayerUI_Island_Infor;

	island_infor->SetLoadLinkIsland(player);
	ship_list->SetLoadLinkPlayer(player);
	
	ship_list->initialize(m_pGraphics, m_pInput, _pt, _width, _height);
	island_infor->initialize(m_pGraphics, m_pInput, _pt, _width, _height);
}

//**********	hide button ship list & island infor ui	**********//
void CWorld_Player_Island_UI::hide_UI()
{
	if (is_show == false)
		return;

	is_show = false;

	ship_list->set_init(false);
	island_infor->set_init(false);

	SAFE_DELETE(ship_list);
	SAFE_DELETE(island_infor);

	ship_list = nullptr;
	island_infor = nullptr;
}

void CWorld_Player_Island_UI::w_move_ud(float _speed)
{
	if (is_show == false)
		return;

	ship_list->w_move_ud(_speed);
	island_infor->w_move_ud(_speed);
}

void CWorld_Player_Island_UI::w_move_rl(float _speed)
{
	if (is_show == false)
		return;

	ship_list->w_move_rl(_speed);
	island_infor->w_move_rl(_speed);
}
