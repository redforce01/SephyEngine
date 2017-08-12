#include "stdafx.h"
#include "gameRespawn_Button.h"
#include "mapSystem.h"

GameRespawn_Button::GameRespawn_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


GameRespawn_Button::~GameRespawn_Button()
{
}

bool GameRespawn_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionGameRespawn, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, gameRespawnButtonNS::FONT_HEIGHT, false, false, gameRespawnButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(gameRespawnButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(gameRespawnButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void GameRespawn_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void GameRespawn_Button::render()
{
	SystemUIButton::render();
}

void GameRespawn_Button::functionGameRespawn(void * obj)
{
	GameRespawn_Button* pThis = (GameRespawn_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(gameRespawnButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(gameRespawnButtonNS::FONT_COLOR_INACTIVE);
	}
}
