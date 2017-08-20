#pragma once

#include "world_Resource_UI.h"
#include "world_Turn_UI.h"
#include "world_Log_UI.h"
#include "world_Minimap_UI.h"

class CWorld_Player;
class CWorld_Scene_UI
{
private:
	CWorld_Player* player;
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_Resource_UI*		w_resource_ui;
	CWorld_Turn_UI*			w_turn_ui;
	CWorld_Log_UI*			w_log_ui;
	CWorld_Minimap_UI*		w_minimap_ui;

	bool is_update;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Scene_UI();
	~CWorld_Scene_UI();

	void initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	void set_is_update(bool _is) { is_update = _is; }
	void print_world_log(const std::string message) { w_log_ui->print_world_log(message); }

	std::deque<std::string> get_log_message() { return w_log_ui->get_log_message(); }
};
