#include "stdafx.h"
#include "lobby_Change_MapTool.h"


bool CLobby_Change_MapTool::initialize(Graphics * g, Input * i)
{
	return false;
}

CLobby_Change_MapTool::CLobby_Change_MapTool()
{
	SystemUIDialog::backColor = lobby_maptoolNS::BACK_COLOR;
	mouse_up = false;
	is_over = false;

	rt_font = { 0, };
}


CLobby_Change_MapTool::~CLobby_Change_MapTool()
{
}

bool CLobby_Change_MapTool::initialize(Graphics * g, Input * i, int _x, int _y)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(g, i, _x, _y, lobby_maptoolNS::WIDTH, lobby_maptoolNS::HEIGHT, lobby_maptoolNS::MARGIN);

	rt_font = RectMake(
		_x + lobby_maptoolNS::MARGIN,
		_y + lobby_maptoolNS::MARGIN,
		lobby_maptoolNS::WIDTH - lobby_maptoolNS::MARGIN * 2, 
		lobby_maptoolNS::HEIGHT - lobby_maptoolNS::MARGIN * 2
	);

	m_dxFont_N.initialize(g, lobby_maptoolNS::FONT_SIZE, true, false, lobby_maptoolNS::FONT);
	m_dxFont_N.setFontColor(lobby_maptoolNS::FONT_COLOR_NORMAL);
	m_dxFont_O.initialize(g, lobby_maptoolNS::FONT_SIZE, true, false, lobby_maptoolNS::FONT);
	m_dxFont_O.setFontColor(lobby_maptoolNS::FONT_COLOR_OVER);

	return true;
}

void CLobby_Change_MapTool::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (PtInRect(&SystemUIDialog::getDialogRECT(), m_pInput->getMousePt()))
		is_over = true;
	else
		is_over = false;

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&SystemUIDialog::getDialogRECT(), m_pInput->getMousePt()))
			{
				//SCENEMANAGER->changeSceneWithLoading("MapTool", "BattleLoading");
				//SCENEMANAGER->changeScene("MapTool");
			}
		}

		mouse_up = false;
	}
}

void CLobby_Change_MapTool::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	if (is_over)
		m_dxFont_O.print(lobby_maptoolNS::OBJECT, rt_font, DT_VCENTER + DT_CENTER);
	else 
		m_dxFont_N.print(lobby_maptoolNS::OBJECT, rt_font, DT_VCENTER + DT_CENTER);

	m_pGraphics->spriteEnd();
}
