#pragma once

#include "systemButton.h"
#include "world_ShipList_UI.h"

namespace world_p_shiplistNS
{
	const std::string BUTTON_MSG = "Ship List";
	const std::string SOUND_UI = "Open_UI";
	const std::string img_name = "Island_UI_";
	const int width = 108;
	const int height = 46;
	const float APEAR_TIME = 0.3f;

	const int MARGIN = 10;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 14;
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_PlayerUI_ShipList
{
private :
	CWorld_Player* player;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	CWorld_ShipList_UI* ship_list;

	SystemButton* button;

	RECT rt_font;

	float delay;	//move complete

	int margin;

	bool is_init;
	bool is_move;
	bool is_click;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_PlayerUI_ShipList();
	~CWorld_PlayerUI_ShipList();

	void initialize(Graphics* g, Input* i, POINT _pt, int _width, int _height);
	void update(float frameTime);
	void render();

	bool get_show() { return is_click; }

	static void click_event();

	void set_init(bool _is) { is_init = _is; }
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};

