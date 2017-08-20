#pragma once

#include "systemUIDialog.h"
#include "world_Battle_UI.h"

enum class e_worldcg
{
	NONE = 0, BATTLE, MOVE
};

enum class e_direct
{
	RT, LT, RB, LB
};

namespace worldcgNS
{
	const std::string SOUND_MOVE = "Move_Ship";
	const std::string img_battle = "HarborBattle_0";
	const std::string img_move = "HarborMove_";
	const std::string MOVE_LT = "LT";
	const std::string MOVE_LB = "LB";
	const std::string MOVE_RT = "RT";
	const std::string MOVE_RB = "RB";

	const UINT battle_min = 19;
	const UINT battle_max = 72;

	const float speed = 5.0f;
	const float delay = 0.05f;
}

class CWorld_Player;
class CWorld_CG : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	CWorld_Player* user;
	CWorld_Battle_UI* battle_ui;

	e_worldcg current_cg;

	Image* img;

	POINT pt;
	POINT destination;

	e_direct direct;

	UINT move_island;

	float degree;
	float speed;

	bool mouse_up;
	bool is_click;
	bool is_complete;

	UINT img_num;

public:
	void SetLoadLinkUser(CWorld_Player* _user) { user = _user; }

	CWorld_CG();
	~CWorld_CG();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void create_battle_cg(UINT _x, UINT _y);
	void update_battle_cg(float frameTime);
	void create_move_ship_cg(POINT _pt, POINT _destination, UINT _move);
	void update_move_ship_cg();
	void set_is_complete(bool _is) { is_complete = _is; }

	void w_move_ud(float _speed);
	void w_move_lr(float _speed);

	bool get_is_complete() { return is_complete; }

	e_worldcg get_cg() { return current_cg; }
};

