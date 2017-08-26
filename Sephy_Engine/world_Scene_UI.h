#pragma once

#include "world_Resource_UI.h"
#include "world_Turn_UI.h"
#include "world_Log_UI.h"

class CWorld_Player;
class CWorld_Scene_UI
{
private:
	CWorld_Player* player;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_Resource_UI*		w_resource_ui;
	CWorld_Turn_UI*			w_turn_ui;
	CWorld_Log_UI*			w_log_ui;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Scene_UI();
	~CWorld_Scene_UI();

	void initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
	void release();

	void set_is_update(bool _is) { w_turn_ui->set_is_update(_is); }
	void print_world_log(const std::string message) { w_log_ui->print_world_log(message); }

	std::deque<std::string> get_log_message() { return w_log_ui->get_log_message(); }
};

