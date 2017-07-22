#include "stdafx.h"
#include "collisionBox_Button.h"
#include "mapSystem.h"

CollisionBox_Button::CollisionBox_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


CollisionBox_Button::~CollisionBox_Button()
{
}

bool CollisionBox_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionCollisionBox, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, collisionBoxButtonNS::FONT_HEIGHT, false, false, collisionBoxButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(collisionBoxButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(collisionBoxButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CollisionBox_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void CollisionBox_Button::render()
{
	SystemUIButton::render();
}

void CollisionBox_Button::functionCollisionBox(void * obj)
{
	CollisionBox_Button* pThis = (CollisionBox_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(collisionBoxButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(collisionBoxButtonNS::FONT_COLOR_INACTIVE);
	}
}
