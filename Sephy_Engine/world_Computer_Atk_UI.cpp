#include "stdafx.h"
#include "world_Computer_Atk_UI.h"
#include "world_Player.h"
#include "world_Computer.h"
#include "World_MainSystem.h"


CWorld_Computer_Atk_UI::CWorld_Computer_Atk_UI()
{
	w_cg = nullptr;
	w_list = nullptr;

	is_show = false;
}


CWorld_Computer_Atk_UI::~CWorld_Computer_Atk_UI()
{
	if (w_cg != nullptr)
		SAFE_DELETE(w_cg);

	if (w_list != nullptr)
		SAFE_DELETE(w_list);
}

void CWorld_Computer_Atk_UI::initialize(Graphics * g, Input * i)
{
	w_cg = new CWorld_CG;
	w_list = new CWorld_Atk_List_UI;

	w_cg->initialize(g, i);
	w_list->initialize(g, i);

	w_cg->SetLoadLinkUser(player);
	w_list->SetLoadLinkPlayer(player);
	w_list->SetLoadLinkUI(this);

	m_pGraphics = g;
	m_pInput = i;

}

void CWorld_Computer_Atk_UI::update(float frameTime)
{
	if (is_show == false)
		return;

	if (w_cg->get_is_complete() == false)
	{
		w_cg->SetLoadLinkUser(player);
		w_cg->update(frameTime);
	}
	else
	{
		w_list->SetLoadLinkPlayer(player);
		w_list->update(frameTime);
	}
}

void CWorld_Computer_Atk_UI::render()
{
	if (is_show == false)
		return;

	if (w_cg->get_is_complete() == false)
		w_cg->render();
	else
	{
		w_list->SetLoadLinkPlayer(player);
		w_list->render();
	}
}

void CWorld_Computer_Atk_UI::release()
{
	if (w_cg != nullptr)
	{
		w_cg->release();
		SAFE_DELETE(w_cg);
	}

	if (w_list != nullptr)
	{
		w_list->release();
		SAFE_DELETE(w_list);
	}
}

//**********	computer's attack animation start		**********//
void CWorld_Computer_Atk_UI::start_event(int _start, int _destination)
{
	is_show = true;

	start_island = _start;
	battle_island = _destination;

	w_cg->create_move_ship_cg(player->get_data()->get_Island()[_start]->getPt(), player->get_data()->get_Island()[_destination]->getPt(), _destination);

	w_list->set_battle_island(_destination);

	float _x = player->get_data()->get_Island()[_destination]->getPt().x;
	float _y = player->get_data()->get_Island()[_destination]->getPt().y;

	player->get_scene()->jump_camera(_x, _y);
}
