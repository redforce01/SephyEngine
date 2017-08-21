#pragma once

#include <sstream>
#include "game.h"
//#include "world_Resource_UI.h"
//#include "world_Turn_UI.h"
//#include "world_Log_UI.h"
//#include "world_Minimap_UI.h"
#include "world_Scene_UI.h"

#include "World_Island_Data.h"
//#include "world_Action_Ship.h"

#include "world_Player.h"
#include "world_Computer.h"
//#include "world_Battle_UI.h"
#include "world_CG.h"

namespace worldmapNS
{
	const UINT SOUND_LIST = 5;
	const std::string SOUND_BGM = "world_theme";

	const std::string IS_STATE_NAME = "World_Game_State";
	const std::string LOAD_NAME = "World_Save_Data";

	const std::string FILE_START = "BEGIN";
	const std::string FILE_FINISH = "END";

	const float margin = 30.0f;
	const std::string img_name = "wmap";

	const float speed = 10.0f;
	const UINT width = 4261;
	const UINT height = 2067;
}

class CWorld_Scene : public Game
{
private:
	CWorld_Player* player;
	CWorld_Computer* computer;

	//UI 들
	CWorld_Scene_UI* w_scene_ui;
	//CWorld_Resource_UI*		w_resource_ui;
	//CWorld_Turn_UI*			w_turn_ui;
	//CWorld_Log_UI*			w_log_ui;
	//CWorld_Minimap_UI*		w_minimap_ui;
	
	//CWorld_Battle_UI* w_battle_ui;

	CWorld_Island_Data*	data_island;	//only data
	//CBuilding* data_building;		//only data -> like data_island

	//CWorld_Action_Ship* w_action_ship;	//배들 관리

	std::vector<CWorld_CG*> w_cg;
	std::vector<std::string> save;
	std::vector<std::string> bgm_list;

	//std::vector<CWorld_Island*> w_current_island;	//my island (점령한 섬)
	//건물 건설하는 것 코딩하기

	Image* worldImage;	//worldmap image

	float worldSpeed;	//worldmap move speed

	bool my_turn;

	void worldMove();	//worldmap move key & limit area
	void init_position();	//atapt margin
	bool data_load();
	void battle_result_load();
	void save_data();

public:
	CWorld_Scene();
	~CWorld_Scene();

	std::vector<std::string> loadObjectData(std::string name);
	std::deque<std::string> get_log_message() { return w_scene_ui->get_log_message(); }

	void add_CG(CWorld_CG* _cg) { w_cg.emplace_back(_cg); }
	void print_world_log(const std::string message) { w_scene_ui->print_world_log(message); }
	void setSpeed(float speed);	//set worldmap move speed

	float getSpeed();	//get worldmap move speed

	void turn_end();

	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

