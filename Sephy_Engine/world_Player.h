#pragma once

#include "world_User.h"
#include "world_Player_Island_UI.h"
#include "world_Island_Detail_UI.h"

namespace world_playerNS
{
	const std::string SOUND_ISLAND = "Click_Island";

	const std::string FLAG_NAME = "Player_Flag";
	const UINT FLAG_WIDTH = 30;
	const UINT FLAG_HEIGHT = 30;
}

class CWorld_Scene_UI;
class CWorld_Island_Data;
class CWorld_Player : public CWorld_User
{
private:
	CWorld_Island_Detail_UI* detail_ui;
	CWorld_Player_Island_UI* island_ui;
	CWorld_Island* select_island;

	//std::vector<CProduction_Ship*> current_ship;
	//UINT current_building[world_island_infor_buildNS::MAX_BOX];

	//CWorld_Island_Data* island_data;
	std::vector<Image*> img_list;

	UINT turn;

	//bool show_ui;

public:
	//void SetLoadLinkData(CWorld_Island_Data* _data) { island_data = _data; }
	void SetLoadLinkUI(CWorld_Scene_UI* _scene_ui) { island_ui->SetLoadLinkUI(_scene_ui); }	

	CWorld_Player();
	~CWorld_Player();

	void initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research) override;
	void update(float frameTime);
	void render();
	//void add_cur_ship(CProduction_Ship* _ship) { current_ship.emplace_back(_ship); }
	//void add_cur_building(UINT _index) { current_building[_index]++; }

	//CWorld_Island_Data* get_data() { return island_data; }
	//CWorld_Island* click_island();
	CWorld_Island* get_select_island() { return select_island; }
	CWorld_Scene* get_scene() { return scene; }
	UINT get_turn() { return turn; }

	void setTurn(int _turn) { turn = _turn; }
	void cancel_ui();
	void click_island();
	void new_player();

	void turn_end();

	//건물 생성 될 때마다 건물 갯수 추가

	//std::vector<CProduction_Ship*> get_cur_ship() { return current_ship; }
	//UINT get_cur_building(UINT _index) { return current_building[_index]; }

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};
