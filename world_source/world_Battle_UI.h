#pragma once

#include "systemUIDialog.h"

namespace worldbattleNS
{
	const std::string INFOR = "UILine_LT";
	const std::string START = "UILine_LB";
	const std::string RETREAT = "UILine_RT";
	const std::string AUTO = "UILine_RB";

	const UINT width = 140;	//image
	const UINT height = 20;
	const UINT x = 100;	//move point
	const UINT y = 20;

	const UINT text_width = 140;
	const UINT text_height = 30;

	const UINT MARGIN = 20;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 30;
	const int FONT_HEIGHT = 30;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Battle_UI : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	Image* battle_infor;
	Image* battle_start;
	Image* battle_retreat;
	Image* auto_battle;

	RECT rt_infor;
	RECT rt_start;
	RECT rt_retreat;
	RECT rt_auto;

	bool visible;

public:
	CWorld_Battle_UI();
	~CWorld_Battle_UI();

	bool initialize(Graphics* g, Input* i, UINT _x, UINT _y);
	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

