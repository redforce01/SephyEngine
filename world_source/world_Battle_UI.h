#pragma once

#include "systemUIDialog.h"
#include "world_Battle_Infor_UI.h"

namespace worldbattleNS
{
	const std::string SOUND_OPEN = "Open_UI";

	// save infor
	const UINT KINE_RESOURCE = 4;
	const std::string FILE_PATH = "Resources\\42_WorldData\\World_Save_Data.txt";
	const std::string FILE_START = "BEGIN\t";
	const std::string FILE_FINISH = "\tEND\n";

	const UINT ACTION_SIZE = 3;

	const std::string INFOR = "UILine_LT";
	const std::string START = "UILine_LB";
	const std::string RETREAT = "UILine_RT";
	const std::string AUTO = "UILine_RB";

	const UINT width = 140;	//image
	const UINT height = 20;
	const UINT x = 100;	//move point
	const UINT y = 20;
	
	const UINT text_width = 140;
	const UINT text_height = 30;

	const UINT MARGIN = 20;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 30;
	const int FONT_HEIGHT = 30;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_CG;
class CWorld_Player;
class CWorld_Battle_UI : public SystemUIDialog
{
private:
	CWorld_Player* player;
	CWorld_CG* cg;

	CWorld_Battle_Infor_UI* infor_ui;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;
	TextDX m_test_font;

	Image* battle_infor;
	Image* battle_start;
	Image* battle_retreat;
	Image* auto_battle;

	RECT rt_infor;
	RECT rt_start;
	RECT rt_retreat;
	RECT rt_auto;

	RECT rt_total;

	UINT battle_island;

	std::vector<std::string> save;

	bool visible;
	bool mouse_up;

	virtual bool initialize(Graphics* g, Input* i) override;

	void save_data();
	void back_island();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkCG(CWorld_CG* _cg) { cg = _cg; }

	CWorld_Battle_UI();
	~CWorld_Battle_UI();

	bool initialize(Graphics* g, Input* i, int _x, int _y);
	
	virtual void update(float frameTime) override;
	virtual void render() override;

	bool get_visible() { return visible; }
	
	void set_battle_island(UINT _island) { battle_island = _island; }

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};

