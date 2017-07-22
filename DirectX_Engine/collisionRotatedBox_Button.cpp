#include "stdafx.h"
#include "collisionRotatedBox_Button.h"
#include "mapSystem.h"

CollisionRotatedBox_Button::CollisionRotatedBox_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


CollisionRotatedBox_Button::~CollisionRotatedBox_Button()
{
}

bool CollisionRotatedBox_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionCollisionRotatedBox, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, collisionRotatedBoxButtonNS::FONT_HEIGHT, false, false, collisionRotatedBoxButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(collisionRotatedBoxButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(collisionRotatedBoxButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CollisionRotatedBox_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void CollisionRotatedBox_Button::render()
{
	SystemUIButton::render();
}

void CollisionRotatedBox_Button::functionCollisionRotatedBox(void * obj)
{
	CollisionRotatedBox_Button* pThis = (CollisionRotatedBox_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(collisionRotatedBoxButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(collisionRotatedBoxButtonNS::FONT_COLOR_INACTIVE);
	}
}
