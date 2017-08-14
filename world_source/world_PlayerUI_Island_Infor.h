#pragma once

#include "systemButton.h"
#include "World_Island_Infor_UI.h"

namespace world_p_island_inforNS
{
	const std::string img_name = "Island_UI_";
	const UINT width = 108;
	const UINT height = 46;
	const float APEAR_TIME = 0.3f;
}

class CWorld_Player;
class CWorld_PlayerUI_Island_Infor
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_Island_Infor_UI* infor_ui;
	CWorld_Player* player;

	SystemButton* button;

	UINT margin;
	float delay;	//move complete time

	bool is_init;	//initialize
	bool is_move;	//move complete
	bool is_click;	//click (show ui)

public:
	void SetLoadLinkIsland(CWorld_Player* _player) { player = _player; }

	CWorld_PlayerUI_Island_Infor();
	~CWorld_PlayerUI_Island_Infor();

	void initialize(Graphics* g, Input* i, POINT _pt, UINT _width, UINT _height);
	void update(float frameTime);
	void render();

	bool get_show() { return is_click; }

	static void click_event();
	void set_init(bool _is) { is_init = _is; }

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};
