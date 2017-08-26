#pragma once

#include "systemUIDialog.h"
#include "world_PlayerUI_Island_Infor.h"
#include "world_PlayerUI_ShipList.h"

class CWorld_Player;
class CWorld_Scene_UI;
class CWorld_Player_Island_UI : public SystemUIDialog
{
private :
	CWorld_Player* player;
	CWorld_Scene_UI* scene_ui;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	CWorld_PlayerUI_ShipList* ship_list;
	CWorld_PlayerUI_Island_Infor* island_infor;

	bool is_show;

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }
	void SetLoadLinkUI(CWorld_Scene_UI* _scene_ui) { scene_ui = _scene_ui; }

	CWorld_Player_Island_UI();
	~CWorld_Player_Island_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	void show_UI(POINT _pt, int _width, int _height);
	void hide_UI();
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);

	bool get_show()
	{ 
		if (ship_list != nullptr)	//show ui
		{
			if (ship_list->get_show() == true)
				return false;
		}
		
		if (island_infor != nullptr)
		{
			if (island_infor->get_show() == true)
				return false;
		}

		return is_show; 
	}
};

