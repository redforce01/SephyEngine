#pragma once

#include "systemUIDialog.h"

namespace lobby_maptoolNS
{
	const std::string SOUNE_BGM = "wating_room";

	const UINT WIDTH = 150;
	const UINT HEIGHT = 40;

	const UINT MARGIN = 10;

	const std::string OBJECT = "Map Tool";

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 20;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR_OVER = graphicsNS::GREEN;    // color of console text
	const COLOR_ARGB FONT_COLOR_NORMAL = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
}

class CLobby_Change_MapTool : public SystemUIDialog
{
private :
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont_N;
	TextDX m_dxFont_O;

	RECT rt_font;

	bool mouse_up;
	bool is_over;

	virtual bool initialize(Graphics* g, Input* i) override;

public:
	CLobby_Change_MapTool();
	~CLobby_Change_MapTool();

	bool initialize(Graphics* g, Input* i, int _x, int _y);
	virtual void update(float frameTime) override;
	virtual void render() override;
};

