#pragma once

namespace world_island_detailNS
{
	const int MARGIN = 10;

	const std::string DETAIL_NAME = "Island_Detail_bg";
	const int DETAIL_WIDTH = 120;
	const int DETAIL_HEIGHT = 80;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 15;
	const int FONT_HEIGHT = 16;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Island;
class CWorld_Island_Detail_UI
{
private :
	CWorld_Island* island;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	Image* background;

	RECT rt_money;
	RECT rt_iron;
	RECT rt_fuel;
	RECT rt_research;

	bool is_show;

	int money;
	int iron;
	int fuel;
	int research;

public:
	CWorld_Island_Detail_UI();
	~CWorld_Island_Detail_UI();

	void initialize(Graphics* g, Input* i, CWorld_Island* _island);
	void update(float frameTime);
	void render();
	void release();

	bool get_is_show() { return is_show; }

	void set_is_show(bool _is) { is_show = _is; }
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};

