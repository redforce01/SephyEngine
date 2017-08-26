#pragma once

#include "world_Ship_Move_UI.h"

namespace world_all_shiplistNS
{
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_CANCEL = "Cancel";
	const std::string SOUND_CLOSE = "Close";

	const std::string BACK_NAME = "ShipList";

	const int WIDTH = 395;
	const int HEIGHT = 595;

	const int MARGIN = 10;

	const int X = 17;
	const int Y = 54;

	//exit infor
	const int EXIT_WIDTH = 20;
	const int EXIT_HEIGHT = 20;
	const float EXIT_WEIGHT = 2.0f;
	const COLOR_ARGB EXIT_COLOR = graphicsNS::RED;

	const int MID_MARGIN = 45;

	const int RT_WIDTH = 158;
	const int RT_HEIGHT = 484;

	const int LIST_WIDTH = 130;
	const int LIST_HEIGHT = 20;
	const int LINE = 22;

	const int MOVE_WIDTH = 200;
	const int MOVE_HEIGHT = 30;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 17;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_OVER = graphicsNS::GREEN;
}

class CWorld_Player;
class CWorld_ShipList_UI
{
private:
	CWorld_Player* player;

private :
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
	std::vector<std::string> island_ship_name;
	std::vector<std::string> current_ship_name;

	int scroll_mount_island;
	int scroll_mount_current;

	bool mouse_up;
	bool is_show;

	void exit_button_render();
	void rt_make_list();
	void scroll();
	void event_click();

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

