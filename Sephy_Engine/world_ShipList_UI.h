#pragma once

#include "world_Ship_Move_UI.h"

namespace world_all_shiplistNS
{
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_CANCEL = "Cancel";
	const std::string SOUND_CLOSE = "Close";

	const std::string BACK_NAME = "ShipList";

	const UINT WIDTH = 395;
	const UINT HEIGHT = 595;

	const UINT MARGIN = 10;

	const UINT X = 17;
	const UINT Y = 54;

	//exit infor
	const UINT EXIT_WIDTH = 20;
	const UINT EXIT_HEIGHT = 20;
	const float EXIT_WEIGHT = 2.0f;
	const COLOR_ARGB EXIT_COLOR = graphicsNS::RED;

	const UINT MID_MARGIN = 45;

	const UINT RT_WIDTH = 158;
	const UINT RT_HEIGHT = 484;

	const UINT LIST_WIDTH = 130;
	const UINT LIST_HEIGHT = 20;
	const int LINE = 22;

	const UINT MOVE_WIDTH = 200;
	const UINT MOVE_HEIGHT = 30;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 17;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_OVER = graphicsNS::GREEN;
}

class CWorld_Player;
class CWorld_ShipList_UI
{
private :
	CWorld_Player* player;
	CWorld_Ship_Move_UI* move;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;
	TextDX m_dxFont_over;

	Image* background;

	RECT rt_exit;
	RECT rt_ship_island;
	RECT rt_ship_current;
	RECT rt_move;

	std::vector<RECT> rt_island;
	std::vector<RECT> rt_current;

	int scroll_mount_island;
	int scroll_mount_current;

	bool mouse_up;
	bool is_show;

	void exit_button_render();
	void rt_make_list();
	void scroll();
	void event_click();
	//void exit();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_ShipList_UI();
	~CWorld_ShipList_UI();

	virtual bool initialize(Graphics* g, Input* i);
	virtual void update(float frameTime);
	virtual void render();

	void delete_move();

	bool get_show() { return is_show; }
};

