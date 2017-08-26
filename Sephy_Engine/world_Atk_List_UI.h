#pragma once

namespace world_atk_list_uiNS
{
	const std::string BACK_NAME = "ShipList";

	const int TITLE_WIDTH = 400;
	const int TITLE_HEIGHT = 30;

	const std::string TITLE_MSG = "Attacked By Computer";
	const std::string BATTLE_MSG = "Battle";
	const std::string AUTO_MSG = "Auto Battle";
	const std::string ATK_MSG = "Attack Ship";
	const std::string DEF_MSG = "Defence Ship";

	const int WIDTH = 395;
	const int HEIGHT = 595;

	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 25;

	const int MARGIN = 10;

	const int X = 17;
	const int Y = 54;

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
class CWorld_Computer_Atk_UI;
class CWorld_Atk_List_UI
{
private:
	CWorld_Player* player;
	CWorld_Computer_Atk_UI* w_atk_ui;

private:

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	Image* background;

	RECT rt_title;
	RECT rt_island_title;
	RECT rt_current_title;
	RECT rt_battle;
	RECT rt_auto;
	RECT rt_ship_island;
	RECT rt_ship_battle;

	std::vector<RECT> rt_island;
	std::vector<RECT> rt_current;
	std::vector<std::string> save;

	int battle_island;
	int scroll_mount_island;
	int scroll_mount_current;

	bool mouse_up;

	void rt_make_list();
	void scroll();
	void auto_battle_cacul();
	void save_data();

public:
	void SetLoadLinkUI(CWorld_Computer_Atk_UI* _ui) { w_atk_ui = _ui; }
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Atk_List_UI();
	~CWorld_Atk_List_UI();

	virtual bool initialize(Graphics* g, Input* i);
	virtual void update(float frameTime);
	virtual void render();
	void release();

	int getX() { return background->getX(); }
	int getY() { return background->getY(); }
	int getWidth() { return background->getWidth(); }
	int getHeight() { return background->getHeight(); }

	void set_battle_island(int _island) { battle_island = _island; }
};
