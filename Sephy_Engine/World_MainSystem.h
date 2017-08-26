#pragma once

#include "World_Island_Data.h"
#include "world_Scene_UI.h"
#include "world_Player.h"
#include "world_Computer.h"
#include "world_CG.h"
#include "systemBase.h"
#include "Battle_DataParser.h"


namespace world_systemNS
{
	const int SOUND_LIST = 5;
	const std::string SOUND_BGM		= "world_theme";
	const std::string FILE_PATH		= "Resources\\50_BattleGameData\\Battle_Result.txt";
	const std::string IS_STATE_NAME = "World_Game_State";
	const std::string LOAD_NAME		= "World_Save_Data";
	const std::string COMPUTER_NAME = "World_Computer_data";
	const std::string FILE_START	= "BEGIN";
	const std::string FILE_FINISH	= "END";
	const std::string img_name		= "wmap";

	const float margin = 30.0f;
	const float speed = 10.0f;
	const int width = 4261;
	const int height = 2067;
}

class CWorld_MainSystem : public SystemBase
{
private:
	CWorld_Player* player;
	CWorld_Computer* computer;

	CWorld_Scene_UI* w_scene_ui;	//UI ต้

	CWorld_Island_Data*	data_island;	//only data

	std::vector<CWorld_CG*> w_cg;	//battle & move cg
	std::vector<std::string> save;	//save data string
	std::vector<std::string> bgm_list;	

	Image* worldImage;	//worldmap image

	float worldSpeed;	//worldmap move speed

	bool my_turn;

	bool data_load();	//data load
	void worldMove();	//worldmap move key & limit area
	void init_position();	//atapt margin
	void computer_data(CWorld_Island* _island);	//computer's load
	void battle_result_load();
	void save_data();

public:
	CWorld_MainSystem();
	~CWorld_MainSystem();

	std::vector<std::string> loadObjectData(std::string name);
	std::deque<std::string> get_log_message() { return w_scene_ui->get_log_message(); }

	void add_CG(CWorld_CG* _cg) { w_cg.emplace_back(_cg); }
	void print_world_log(const std::string message) { w_scene_ui->print_world_log(message); }
	void jump_camera(float _x, float _y);	//camera location

	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
	
	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();
};

