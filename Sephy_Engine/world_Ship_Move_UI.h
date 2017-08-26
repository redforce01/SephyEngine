#pragma once

#include "world_Island.h"
#include "world_CG.h"

class CWorld_Player;
class CWorld_ShipList_UI;
class CWorld_Ship_Move_UI
{
private :
	CWorld_Player* player;
	CWorld_ShipList_UI* list_ui;

private :
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::vector<CWorld_Island*> can_island;

	bool mouse_up;

	void click_event(CWorld_Island* _island);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkListUI(CWorld_ShipList_UI* _ui) { list_ui = _ui; }

	CWorld_Ship_Move_UI();
	~CWorld_Ship_Move_UI();

	void initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	void add_island(CWorld_Island* _island) { can_island.emplace_back(_island); }
};

