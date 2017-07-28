#pragma once

#include "systemUIDialog.h"

enum class e_worldcg
{
	NONE = 0, BATTLE, MOVE
};

namespace worldcgNS
{
	const UINT battle_min = 19;
	const UINT battle_max = 72;
}

class CWorld_CG : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	e_worldcg current_cg;

	Image* img;

public:
	CWorld_CG();
	~CWorld_CG();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void create_battle_cg(UINT _x, UINT _y);
	void create_move_ship_cg(POINT _pt, POINT _destination);
};

