#include "stdafx.h"
#include "world_Scene_UI.h"
#include "world_Player.h"

CWorld_Scene_UI::CWorld_Scene_UI()
{
	w_resource_ui = new CWorld_Resource_UI;
	w_turn_ui = new CWorld_Turn_UI;
	w_log_ui = new CWorld_Log_UI;
	w_minimap_ui = new CWorld_Minimap_UI;

	is_update = true;
}


CWorld_Scene_UI::~CWorld_Scene_UI()
{
}

void CWorld_Scene_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	w_resource_ui->SetLoadLinkPlayer(player);
	w_turn_ui->SetLoadLinkPlayer(player);

	w_resource_ui->initialize(g, i);
	w_turn_ui->initialize(g, i);
	w_log_ui->initialize(g, i);
	//w_minimap_ui->initialze(this->graphics, this->input);
}

void CWorld_Scene_UI::update(float frameTime)
{
	w_resource_ui->update(frameTime);
	w_log_ui->update(frameTime);

	if (is_update == false)
		return;
	
	w_turn_ui->update(frameTime);
}

void CWorld_Scene_UI::render()
{
	w_resource_ui->render();
	w_turn_ui->render();
	w_log_ui->render();
}
