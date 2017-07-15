#pragma once

#include "game.h"
#include "world_Resource_UI.h"
#include "world_Turn_UI.h"
#include "world_Log_UI.h"
#include "world_Minimap_UI.h"

namespace worldmapNS
{
	const float margin = 30.0f;
	const std::string img_name = "wmap";
}

class CWorld_Scene : public Game
{
private:
	CWorld_Resource_UI*	w_resource_ui;
	CWorld_Turn_UI*			w_turn_ui;
	CWorld_Log_UI*			w_log_ui;
	CWorld_Minimap_UI*	w_minimap_ui;

	class CBuilding		//building infor
	{
		UINT id;		//building unique number
		UINT type;		//building type

		bool in_production;	//use building
	};

	class CNeighborhood_Island	//neighborhood island infor
	{
		UINT id;		//n_island unique number
		UINT type;		//n_island type -> build & resouce island

		UINT resource;	//if type == resouce_island else 0

		CBuilding building;	//if type == build_island else null
	};

	class CWorld_Island	//island infor
	{
		UINT id;		//island unique number

		float x;			//island x position (standard world)
		float y;			//island y position (standard world)
		float width;	//island collision width;
		float height;	//island collision height;

		bool u_island;	//can go island

		UINT* nextnode;	//island connect nodes
		CNeighborhood_Island* n_island;	//island's near neighborhood island
	};

	Image* worldImage;	//worldmap image

	float worldSpeed;	//worldmap move speed

	void worldMove();	//worldmap move key & limit area

public:
	CWorld_Scene();
	~CWorld_Scene();

	void setSpeed(float speed);	//set worldmap move speed

	float getSpeed();	//get worldmap move speed

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

