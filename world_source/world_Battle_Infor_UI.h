#pragma once

namespace world_battle_infor_uiNS
{
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

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 17;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_OVER = graphicsNS::GREEN;
}

class CWorld_Player;
class CWorld_Battle_Infor_UI
{
private:
	CWorld_Player* player;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	Image* background;

	RECT rt_exit;
	RECT rt_ship_island;
	RECT rt_ship_battle;

	UINT battle_island;

	std::vector<RECT> rt_island;
	std::vector<RECT> rt_current;

	int scroll_mount_island;
	int scroll_mount_current;

	bool mouse_up;
	bool is_show;

	void exit_button_render();
	void rt_make_list();
	void scroll();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Battle_Infor_UI();
	~CWorld_Battle_Infor_UI();

	virtual bool initialize(Graphics* g, Input* i);
	virtual void update(float frameTime);
	virtual void render();

	void set_battle_island(UINT _island) { battle_island = _island; }
	void set_is_show(bool _is) { is_show = _is; }

	bool get_is_show() { return is_show; }
};

