#pragma once

namespace world_battle_infor_uiNS
{
	const std::string SOUND_CLOSE = "Close";

	const std::string BACK_NAME = "ShipList";

	const std::string ATK_MSG = "Attack Ship";
	const std::string DEF_MSG = "Defence Ship";

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

	const int TITLE_WIDTH = 158;
	const int TITLE_HEIGHT = 30;

	const int MID_MARGIN = 45;

	const int RT_WIDTH = 158;
	const int RT_HEIGHT = 484;

	const int LIST_WIDTH = 130;
	const int LIST_HEIGHT = 20;
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
private :
	CWorld_Player* player;

private:

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	Image* background;

	RECT rt_island_title;
	RECT rt_current_title;

	RECT rt_exit;
	RECT rt_ship_island;
	RECT rt_ship_battle;

	std::vector<RECT> rt_island;
	std::vector<RECT> rt_current;

	int battle_island;
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
	void release();

	int getX() { return background->getX(); }
	int getY() { return background->getY(); }
	int getWidth() { return background->getWidth(); }
	int getHeight() { return background->getHeight(); }

	void set_battle_island(int _island) { battle_island = _island; }
	void set_is_show(bool _is) { is_show = _is; }

	bool get_is_show() { return is_show; }
};

