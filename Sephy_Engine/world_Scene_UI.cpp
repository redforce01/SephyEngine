#include "stdafx.h"
#include "world_Scene_UI.h"
#include "world_Player.h"

CWorld_Scene_UI::CWorld_Scene_UI()
{
}


CWorld_Scene_UI::~CWorld_Scene_UI()
{
	SAFE_DELETE(w_resource_ui);
	SAFE_DELETE(w_turn_ui);
	SAFE_DELETE(w_log_ui);
}

void CWorld_Scene_UI::initialize(Graphics * g, Input * i)
{
	w_resource_ui = new CWorld_Resource_UI;
	w_turn_ui = new CWorld_Turn_UI;
	w_log_ui = new CWorld_Log_UI;

	m_pGraphics = g;
	m_pInput = i;

	w_resource_ui->SetLoadLinkPlayer(player);
	w_turn_ui->SetLoadLinkPlayer(player);

	w_resource_ui->initialize(g, i);
	w_turn_ui->initialize(g, i);
	w_log_ui->initialize(g, i);
}

void CWorld_Scene_UI::update(float frameTime)
{
	w_resource_ui->update(frameTime);
	w_log_ui->update(frameTime);
	w_turn_ui->update(frameTime);
}

void CWorld_Scene_UI::render()
{
	w_resource_ui->render();
	w_turn_ui->render();
	w_log_ui->render();
}

void CWorld_Scene_UI::release()
{
	w_resource_ui->release();
	w_turn_ui->release();
	w_log_ui->release();

	SAFE_DELETE(w_resource_ui);
	SAFE_DELETE(w_turn_ui);
	SAFE_DELETE(w_log_ui);
}
