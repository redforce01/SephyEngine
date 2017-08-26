#include "stdafx.h"
#include "lobby_Menu.h"

bool CLobby_Menu::initialize(Graphics * g, Input * i)
{
	return false;
}

CLobby_Menu::CLobby_Menu()
{
	SystemUIDialog::backColor = lobby_menuNS::BACK_COLOR;
	
	mouse_up = false;

	rt_campagin = { 0, };
	rt_option = { 0, };
	rt_credit = { 0, };
	rt_exit = { 0, };
}
CLobby_Menu::~CLobby_Menu()
{
}

bool CLobby_Menu::initialize(Graphics * g, Input * i, int _x, int _y)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(g, i, _x, _y, lobby_menuNS::WIDTH, lobby_menuNS::HEIGHT, lobby_menuNS::MARGIN);

	rt_campagin = RectMake(
		_x + lobby_menuNS::MARGIN,
		_y + lobby_menuNS::MARGIN,
		lobby_menuNS::RT_WIDTH,
		lobby_menuNS::RT_HEIGHT
	);
	
	rt_option = RectMake(rt_campagin.left, rt_campagin.bottom, lobby_menuNS::RT_WIDTH, lobby_menuNS::RT_HEIGHT);
	rt_credit = RectMake(rt_option.left, rt_option.bottom, lobby_menuNS::RT_WIDTH, lobby_menuNS::RT_HEIGHT);
	rt_exit = RectMake(rt_credit.left, rt_credit.bottom, lobby_menuNS::RT_WIDTH, lobby_menuNS::RT_HEIGHT);

	m_dxFont_N.initialize(g, lobby_menuNS::FONT_SIZE, true, false, lobby_menuNS::FONT);
	m_dxFont_N.setFontColor(lobby_menuNS::FONT_COLOR_NORMAL);
	m_dxFont_O.initialize(g, lobby_menuNS::FONT_SIZE, true, false, lobby_menuNS::FONT);
	m_dxFont_O.setFontColor(lobby_menuNS::FONT_COLOR_OVER);

	return true;
}

void CLobby_Menu::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_campagin, m_pInput->getMousePt()))
			{
				std::vector<std::string> temp;
				temp.emplace_back(lobby_menuNS::NEW);

				TXTDATA_PARSER->saveDataFromArray(lobby_menuNS::FILE_PATH, temp);

				SCENEMANAGER->changeScene("World");
			}
			if (PtInRect(&rt_option, m_pInput->getMousePt()))
			{
			}
			if (PtInRect(&rt_credit, m_pInput->getMousePt()))
			{
			}
			if (PtInRect(&rt_exit, m_pInput->getMousePt()))
			{
				PostQuitMessage(0);
			}
		}

		mouse_up = false;
	}
}

void CLobby_Menu::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	if (PtInRect(&rt_campagin, m_pInput->getMousePt()))
		m_dxFont_O.print(lobby_menuNS::NEW_CAMPAGIN, rt_campagin, DT_VCENTER + DT_LEFT);
	else 
		m_dxFont_N.print(lobby_menuNS::NEW_CAMPAGIN, rt_campagin, DT_VCENTER + DT_LEFT);

	if (PtInRect(&rt_option, m_pInput->getMousePt()))
		m_dxFont_O.print(lobby_menuNS::OPTION, rt_option, DT_VCENTER + DT_LEFT);
	else
		m_dxFont_N.print(lobby_menuNS::OPTION, rt_option, DT_VCENTER + DT_LEFT);

	if (PtInRect(&rt_credit, m_pInput->getMousePt()))
		m_dxFont_O.print(lobby_menuNS::CREDIT, rt_credit, DT_VCENTER + DT_LEFT);
	else
		m_dxFont_N.print(lobby_menuNS::CREDIT, rt_credit, DT_VCENTER + DT_LEFT);

	if (PtInRect(&rt_exit, m_pInput->getMousePt()))
		m_dxFont_O.print(lobby_menuNS::EXIT, rt_exit, DT_VCENTER + DT_LEFT);
	else
		m_dxFont_N.print(lobby_menuNS::EXIT, rt_exit, DT_VCENTER + DT_LEFT);

	m_pGraphics->spriteEnd();
}
