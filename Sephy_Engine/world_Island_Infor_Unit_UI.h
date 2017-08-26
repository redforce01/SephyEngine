#pragma once

#include "world_Ship_Buy_Infor.h"

namespace world_island_infor_unitNS
{
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_CANCEL = "Cancel";

	const int MARGIN = 10;
	const int BUILDING_MARGIN = 150;

	//build infor
	const std::string UNIT_NAME = "_create";
	const int MAX_UNIT = 3;
	const int UNIT_WIDTH = 40;		//165
	const int UNIT_HEIGHT = 40;	//130

	const int TURN_WIDTH = 130;	//165
	const int TURN_HEIGHT = 30;

	const std::string BOX_NAME = "_make";
	const int MAX_BOX = 15;
	const int BOX_WIDTH = 80;
	const int BOX_HEIGHT = 80;

	//destroy infor
	const std::string DESTROY_IMG = "Destroy_Overlap";
	const int DESTROY_WIDTH = 40;		//185
	const int DESTROY_HEIGHT = 40;		//185
	const COLOR_ARGB DESTROY_COLOR = SETCOLOR_ARGB(180, 255, 255, 255);

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 10;
	const int FONT_HEIGHT = 13;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Island_Infor_UI;
class CWorld_Island_Infor_Unit_UI
{
private :
	CWorld_Player* player;
	CWorld_Island_Infor_UI* infor_ui;

private:
	CWorld_Ship_Buy_Infor* ship_infor;
	CProduction_Ship* ship[world_island_infor_unitNS::MAX_UNIT];

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	int index;
	int current_action;

	RECT rt_unit[world_island_infor_unitNS::MAX_UNIT];
	RECT rt_turn[world_island_infor_unitNS::MAX_UNIT];

	RECT rt_box[world_island_infor_unitNS::MAX_BOX];

	std::vector<Image*> img_list;

	bool mouse_up;

	void rect_initialize(RECT _rtM, RECT _rtR);
	void destroy_button_render(int _index);
	bool is_build(CProduction_Ship* _ship);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkInfor(CWorld_Island_Infor_UI* _infor) { infor_ui = _infor; }

	CWorld_Island_Infor_Unit_UI();
	~CWorld_Island_Infor_Unit_UI();

	CProduction_Ship* get_action(int _index) { return ship[_index]; }

	int get_action_size() { return world_island_infor_unitNS::MAX_UNIT; }

	void initialize(Graphics* g, Input* i, int _index, RECT _rtM, RECT _rtR);
	void update(float frameTime);
	void render();

	void set_action(CProduction_Ship* _ship);
	void w_move_rl(float _speed);
};

