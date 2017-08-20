#pragma once

#include "systemUIDialog.h"

namespace lobby_menuNS
{
	const std::string SOUNE_BGM = "wating_room";

	const UINT WIDTH = 200;
	const UINT HEIGHT = 250;

	const UINT MARGIN = 10;

	const std::string NEW_CAMPAGIN = "New Campagin";
	const std::string OPTION = "Option";
	const std::string CREDIT = "Credit";
	const std::string EXIT = "Exit";

	const std::string FILE_PATH = "Resources\\42_WorldData\\World_Game_State.txt";
	const std::string NEW = "New";

	const UINT RT_WIDTH = lobby_menuNS::WIDTH - lobby_menuNS::MARGIN * 2;
	const UINT RT_HEIGHT = lobby_menuNS::HEIGHT / 5;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 20;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR_OVER = graphicsNS::GREEN;    // color of console text
	const COLOR_ARGB FONT_COLOR_NORMAL = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
}

class CLobby_Menu : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont_N;
	TextDX m_dxFont_O;

	RECT rt_campagin;
	RECT rt_option;
	RECT rt_credit;
	RECT rt_exit;

	bool mouse_up;

	virtual bool initialize(Graphics* g, Input* i) override;

public:
	CLobby_Menu();
	~CLobby_Menu();

	bool initialize(Graphics* g, Input* i, int _x, int _y);
	virtual void update(float frameTime) override;
	virtual void render() override;
};

