#include "stdafx.h"
#include "lobby_Change_UnitTool.h"


bool CLobby_Change_UnitTool::initialize(Graphics * g, Input * i)
{
	return false;
}

CLobby_Change_UnitTool::CLobby_Change_UnitTool()
{
	SystemUIDialog::backColor = lobby_unittoolNS::BACK_COLOR;

	mouse_up = false;
	is_over = false;

	rt_font = { 0, };
}


CLobby_Change_UnitTool::~CLobby_Change_UnitTool()
{
}

bool CLobby_Change_UnitTool::initialize(Graphics * g, Input * i, int _x, int _y)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(g, i, _x, _y, lobby_unittoolNS::WIDTH, lobby_unittoolNS::HEIGHT, lobby_unittoolNS::MARGIN);

	rt_font = RectMake(
		_x + lobby_unittoolNS::MARGIN,
		_y + lobby_unittoolNS::MARGIN,
		lobby_unittoolNS::WIDTH - lobby_unittoolNS::MARGIN * 2,
		lobby_unittoolNS::HEIGHT - lobby_unittoolNS::MARGIN * 2
	);

	m_dxFont_N.initialize(g, lobby_unittoolNS::FONT_SIZE, true, false, lobby_unittoolNS::FONT);
	m_dxFont_N.setFontColor(lobby_unittoolNS::FONT_COLOR_NORMAL);
	m_dxFont_O.initialize(g, lobby_unittoolNS::FONT_SIZE, true, false, lobby_unittoolNS::FONT);
	m_dxFont_O.setFontColor(lobby_unittoolNS::FONT_COLOR_OVER);

	return true;
}

void CLobby_Change_UnitTool::update(float frameTime)
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
				//SCENEMANAGER->addScene("UnitTool", new CScene_UnitTool);
			}
		}

		mouse_up = false;
	}
}

void CLobby_Change_UnitTool::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	if (is_over)
		m_dxFont_O.print(lobby_unittoolNS::OBJECT, rt_font, DT_VCENTER + DT_CENTER);
	else
		m_dxFont_N.print(lobby_unittoolNS::OBJECT, rt_font, DT_VCENTER + DT_CENTER);

	m_pGraphics->spriteEnd();
}
