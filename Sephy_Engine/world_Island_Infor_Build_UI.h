#pragma once

#include "world_Building_Buy_Infor.h"

namespace world_island_infor_buildNS
{
	const int MARGIN = 10;

	//build infor
	const int MAX_BOX = 15;
	const float BOX_WIDTH = 80;
	const float BOX_HEIGHT = 80;
	const float BUILDING_SIZE = 150;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 10;
	const int FONT_HEIGHT = 13;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Island_Infor_UI;
class CWorld_Island_Infor_Build_UI
{
private :
	CWorld_Player* player;
	CWorld_Island_Infor_UI* infor_ui;

private:
	CWorld_Building_Buy_Infor* buy_infor;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	RECT rt_box[world_island_infor_buildNS::MAX_BOX];

	std::vector<Image*> img_list;

	int index;

	bool mouse_up;

	bool is_build(CBuilding* _building);	//current player have building
	void rect_initialize(RECT _rt);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkInfor(CWorld_Island_Infor_UI* _infor) { infor_ui = _infor; }

	CWorld_Island_Infor_Build_UI();
	~CWorld_Island_Infor_Build_UI();

	void initialize(Graphics* g, Input* i, int _index, RECT _rt);
	void update(float frameTime);
	void render();

	void w_move_rl(float _speed);
};

