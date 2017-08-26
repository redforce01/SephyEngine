#pragma once

#include "world_User.h"
#include "world_Player_Island_UI.h"
#include "world_Island_Detail_UI.h"
#include "world_Computer_Atk_UI.h"

namespace world_playerNS
{
	const std::string SOUND_ISLAND = "Click_Island";

	const std::string FLAG_NAME = "Player_Flag";
	const int FLAG_WIDTH = 30;
	const int FLAG_HEIGHT = 30;
	const int COST_RANGE = 10;
}

class CWorld_Computer;
class CWorld_Scene_UI;
class CWorld_Island_Data;
class CWorld_Player : public CWorld_User
{
private :
	CWorld_Computer* computer;

private:
	CWorld_Computer_Atk_UI* com_atk_ui;
	CWorld_Island_Detail_UI* detail_ui;
	CWorld_Player_Island_UI* island_ui;
	CWorld_Island* select_island;

	std::vector<Image*> img_list;

	int turn;

	void atk_player();

public:
	void SetLoadLinkUI(CWorld_Scene_UI* _scene_ui) { island_ui->SetLoadLinkUI(_scene_ui); }	
	void SetLoadLinkComputer(CWorld_Computer* _computer) { computer = _computer; }

	CWorld_Player();
	~CWorld_Player();

	void initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research) override;
	void update(float frameTime);
	void render();
	void release();

	CWorld_Island* get_select_island() { return select_island; }
	CWorld_MainSystem* get_scene() { return scene; }
	CWorld_Computer* get_computer() { return computer; }
	
	int get_turn() { return turn; }

	void setTurn(int _turn) { turn = _turn; }
	void cancel_ui();
	void click_island();
	void new_player();

	void turn_end();

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};
