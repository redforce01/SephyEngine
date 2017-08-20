#pragma once

#include "world_Ship_Buy_Infor.h"

namespace world_island_infor_unitNS
{
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_CANCEL = "Cancel";

	const UINT MARGIN = 10;
	const UINT BUILDING_MARGIN = 150;

	//build infor
	const std::string UNIT_NAME = "_create";
	const UINT MAX_UNIT = 3;
	const UINT UNIT_WIDTH = 40;		//165
	const UINT UNIT_HEIGHT = 40;	//130

	const UINT TURN_WIDTH = 130;	//165
	const UINT TURN_HEIGHT = 30;

	const std::string BOX_NAME = "_make";
	const UINT MAX_BOX = 15;
	const UINT BOX_WIDTH = 80;
	const UINT BOX_HEIGHT = 80;

	const float DESTROY_WEIGHT = 2.0f;
	const COLOR_ARGB DESTROY_COLOR = graphicsNS::RED;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 10;
	const int FONT_HEIGHT = 13;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Island_Infor_UI;
class CWorld_Island_Infor_Unit_UI
{
private:
	CWorld_Player* player;
	CWorld_Island_Infor_UI* infor_ui;
	CWorld_Ship_Buy_Infor* ship_infor;
	CProduction_Ship* ship[world_island_infor_unitNS::MAX_UNIT];

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	UINT index;
	int current_action;

	RECT rt_unit[world_island_infor_unitNS::MAX_UNIT];
	RECT rt_turn[world_island_infor_unitNS::MAX_UNIT];

	RECT rt_box[world_island_infor_unitNS::MAX_BOX];

	std::vector<Image*> img_list;

	//bool mouse_up_unit;
	bool mouse_up;

	void rect_initialize(RECT _rtM, RECT _rtR);
	//void build_destroy_render();
	void destroy_button_render(UINT _index);
	bool is_build(CProduction_Ship* _ship);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkInfor(CWorld_Island_Infor_UI* _infor) { infor_ui = _infor; }

	CWorld_Island_Infor_Unit_UI();
	~CWorld_Island_Infor_Unit_UI();

	void initialize(Graphics* g, Input* i, UINT _index, RECT _rtM, RECT _rtR);
	void update(float frameTime);
	void render();

	void set_action(CProduction_Ship* _ship);
	CProduction_Ship* get_action(UINT _index) { return ship[_index]; }
	UINT get_action_size() { return world_island_infor_unitNS::MAX_UNIT; }

	void w_move_rl(float _speed);
};

