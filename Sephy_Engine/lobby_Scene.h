#pragma once

#include "game.h"
#include "lobby_Change_MapTool.h"
#include "lobby_Change_UnitTool.h"
#include "lobby_Change_World.h"
#include "lobby_Menu.h"

namespace lobby_sceneNS
{
	const std::string SOUNE_BGM = "wating_room";

	const std::string BACK_NAME = "Lobby_Background";
	const float BACK_WIDTH = 800;
	const float BACK_HEIGHT = 600;
	const int BACK_MARGIN = 200;

	const int MAP_X = 310;
	const int MAP_Y = 500;

	const int UNIT_X = 1500;
	const int UNIT_Y = 160;

	const int WORLD_Y = 100;

	const int MENU_X = 1500;
	const int MENU_Y = 650;
}

class CLobby_Scene : public Game
{
private :
	Image* background_back;
	Image* background;

	CLobby_Change_MapTool*	l_map;
	CLobby_Change_UnitTool*	l_unit;
	CLobby_Change_World*	l_world;
	CLobby_Menu*			l_menu;

public:
	CLobby_Scene();
	~CLobby_Scene();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

