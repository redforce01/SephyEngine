#pragma once

#include "systemUIDialog.h"
#include "world_Battle_Infor_UI.h"
#include "Battle_DataParser.h"

namespace worldbattleNS
{
	const std::string SOUND_OPEN = "Open_UI";

	const std::string INFOR_MSG = "Battle Info";
	const std::string START_MSG = "Battle Start";
	const std::string RETREAT_MSG = "Retreat";
	const std::string AUTO_MSG = "AUTO Battle";

	// save infor
	const int KINE_RESOURCE = 4;
	const std::string FILE_PATH = "Resources\\40_WorldData\\World_Save_Data.txt";
	const std::string FILE_STATE_PATH = "Resources\\40_WorldData\\World_Game_State.txt";
	const std::string STATE_PLAY = "Play";
	const std::string FILE_START = "BEGIN\t";
	const std::string FILE_FINISH = "END";

	const int ACTION_SIZE = 3;

	const std::string INFOR = "UILine_LT";
	const std::string START = "UILine_LB";
	const std::string RETREAT = "UILine_RT";
	const std::string AUTO = "UILine_RB";

	const int width = 140;	//image
	const int height = 20;
	const int x = 100;	//move point
	const int y = 20;
	
	const int text_width = 140;
	const int text_height = 30;

	const int MARGIN = 20;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 20;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
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

	int battle_island;

	bool visible;
	bool mouse_up;

	std::vector<std::string> save;

	virtual bool initialize(Graphics* g, Input* i) override;

	void auto_battle_cacul();
	void save_data();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkCG(CWorld_CG* _cg) { cg = _cg; }

	CWorld_Battle_UI();
	~CWorld_Battle_UI();

	bool initialize(Graphics* g, Input* i, int _x, int _y);
	
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	bool get_visible() { return visible; }
	
	void set_battle_island(int _island) { battle_island = _island; }
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};

