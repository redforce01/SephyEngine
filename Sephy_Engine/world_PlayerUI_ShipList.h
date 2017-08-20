#pragma once

#include "systemButton.h"
#include "world_ShipList_UI.h"

namespace world_p_shiplistNS
{
	const std::string SOUND_UI = "Open_UI";
	const std::string img_name = "Island_UI_";
	const UINT width = 108;
	const UINT height = 46;
	const float APEAR_TIME = 0.3f;
}

class CWorld_Player;
class CWorld_PlayerUI_ShipList
{
private:
	CWorld_Player* player;

	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_ShipList_UI* ship_list;

	SystemButton* button;

	UINT margin;
	float delay;	//move complete

	bool is_init;
	bool is_move;
	bool is_click;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_PlayerUI_ShipList();
	~CWorld_PlayerUI_ShipList();

	void initialize(Graphics* g, Input* i, POINT _pt, UINT _width, UINT _height);
	void update(float frameTime);
	void render();

	bool get_show() { return is_click; }

	void set_init(bool _is) { is_init = _is; }

	static void click_event();

	void w_move_ud(float _speed) { button->moveY(_speed); }
	void w_move_rl(float _speed) { button->moveX(_speed); }
};

