#include "stdafx.h"
#include "control_ExitButton.h"


Control_ExitButton::Control_ExitButton()
{
}


Control_ExitButton::~Control_ExitButton()
{
}

bool Control_ExitButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionExit, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, exitButtonNS::IMAGE_WIDTH, exitButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(exitButtonNS::FILENAME));
		m_dxFont.initialize(g, exitButtonNS::FONT_HEIGHT, false, false, exitButtonNS::FONT);
		m_dxFont.setFontColor(exitButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(exitButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "EXIT Button Initialize Failed", "Error", MB_OK);
	}

	return success;

	return false;
}

void Control_ExitButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_ExitButton::render()
{
	SystemUIButton::render();
}

void Control_ExitButton::functionExit(void * obj)
{
	PostQuitMessage(0);
}
