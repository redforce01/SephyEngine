#pragma once

#include "world_CG.h"
#include "world_Atk_List_UI.h"

namespace world_com_atkNS
{
	const UINT MARGIN = 10;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 16;
	const int FONT_HEIGHT = 17;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Computer_Atk_UI
{
private :
	CWorld_Player* player;

private :
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_CG* w_cg;
	CWorld_Atk_List_UI* w_list;

	int start_island;
	int battle_island;

	bool is_show;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Computer_Atk_UI();
	~CWorld_Computer_Atk_UI();

	void initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
	void release();

	bool get_is_show() { return is_show; }

	void start_event(int _start , int _destination);
	void set_is_show(bool _is) { is_show = _is; }
	void w_move_ud(float _speed) { w_cg->w_move_ud(_speed); }
	void w_move_rl(float _speed) { w_cg->w_move_lr(_speed); }
};
