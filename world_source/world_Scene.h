#pragma once

#include "game.h"
#include "world_Resource_UI.h"
#include "world_Turn_UI.h"
#include "world_Log_UI.h"
#include "world_Minimap_UI.h"

#include "World_Island_Data.h"
//#include "world_Action_Ship.h"

#include "world_Player.h"
#include "world_Computer.h"
#include "world_Battle_UI.h"

namespace worldmapNS
{
	const float margin = 30.0f;
	const std::string img_name = "wmap";
}

class CWorld_Scene : public Game
{
private:
	CWorld_Player* player;
	CWorld_Computer* computer;

	//UI 들
	CWorld_Resource_UI*	w_resource_ui;
	CWorld_Turn_UI*			w_turn_ui;
	CWorld_Log_UI*			w_log_ui;
	CWorld_Minimap_UI*	w_minimap_ui;
	
	CWorld_Island_Data*	data_island;	//only data
	//CBuilding* data_building;		//only data -> like data_island

	//CWorld_Action_Ship* w_action_ship;	//배들 관리

	CWorld_Battle_UI* w_battle_ui;

	//std::vector<CWorld_Island*> w_current_island;	//my island (점령한 섬)
	//건물 건설하는 것 코딩하기

	Image* worldImage;	//worldmap image

	float worldSpeed;	//worldmap move speed

	bool my_turn;

	void worldMove();	//worldmap move key & limit area

public:
	CWorld_Scene();
	~CWorld_Scene();

	void setSpeed(float speed);	//set worldmap move speed

	float getSpeed();	//get worldmap move speed

	void turn_end();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

