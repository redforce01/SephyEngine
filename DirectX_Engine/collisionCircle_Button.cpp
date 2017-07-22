#include "stdafx.h"
#include "collisionCircle_Button.h"
#include "mapSystem.h"

CollisionCircle_Button::CollisionCircle_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


CollisionCircle_Button::~CollisionCircle_Button()
{
}

bool CollisionCircle_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionCollisionCircle, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, collisionCircleButtonNS::FONT_HEIGHT, false, false, collisionCircleButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(collisionCircleButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(collisionCircleButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CollisionCircle_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void CollisionCircle_Button::render()
{
	SystemUIButton::render();
}

void CollisionCircle_Button::functionCollisionCircle(void * obj)
{
	CollisionCircle_Button* pThis = (CollisionCircle_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(collisionCircleButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(collisionCircleButtonNS::FONT_COLOR_INACTIVE);
	}
}
