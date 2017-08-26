#pragma once

#include "systemButton.h"
#include "World_Island_Infor_UI.h"

namespace world_p_island_inforNS
{
	const std::string BUTTON_MSG = "Island Info";

	const std::string SOUND_OPEN = "Open_Slide";
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
class CWorld_PlayerUI_Island_Infor
{
private :
	CWorld_Player* player;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	CWorld_Island_Infor_UI* infor_ui;

	SystemButton* button;

	RECT rt_font;

	int margin;

	float delay;	//move complete time
	float delay_infor;

	bool is_init;	//initialize
	bool is_move;	//move complete (Island Infor)
	bool is_move_infor;	//infor_ui
	bool is_click;	//click (show ui)

public:
	void SetLoadLinkIsland(CWorld_Player* _player) { player = _player; }

	CWorld_PlayerUI_Island_Infor();
	~CWorld_PlayerUI_Island_Infor();

	void initialize(Graphics* g, Input* i, POINT _pt, int _width, int _height);
	void update(float frameTime);
	void render();

	bool get_show() { return is_click; }

	static void click_event();
	void set_init(bool _is) { is_init = _is; }
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);

};
