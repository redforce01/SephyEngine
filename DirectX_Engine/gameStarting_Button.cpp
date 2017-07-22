#include "stdafx.h"
#include "gameStarting_Button.h"
#include "mapSystem.h"

GameStarting_Button::GameStarting_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


GameStarting_Button::~GameStarting_Button()
{
}

bool GameStarting_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionGameStarting, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, gameStartingButtonNS::FONT_HEIGHT, false, false, gameStartingButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(gameStartingButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(gameStartingButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void GameStarting_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void GameStarting_Button::render()
{
	SystemUIButton::render();
}

void GameStarting_Button::functionGameStarting(void * obj)
{
	GameStarting_Button* pThis = (GameStarting_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(gameStartingButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(gameStartingButtonNS::FONT_COLOR_INACTIVE);
	}
}
