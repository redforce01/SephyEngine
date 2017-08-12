#include "stdafx.h"
#include "control_ResetButton.h"
#include "logViewer.h"
#include "mapSystem.h"

Control_ResetButton::Control_ResetButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_ResetButton::~Control_ResetButton()
{
}

bool Control_ResetButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionReset, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, resetButtonNS::IMAGE_WIDTH, resetButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(resetButtonNS::FILENAME));
		m_dxFont.initialize(g, resetButtonNS::FONT_HEIGHT, false, false, resetButtonNS::FONT);
		m_dxFont.setFontColor(resetButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(resetButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Reset Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_ResetButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_ResetButton::render()
{
	SystemUIButton::render();
}

void Control_ResetButton::functionReset(void * obj)
{
	Control_ResetButton* pThis = (Control_ResetButton*)obj;
	pThis->m_pInput->setMouseLButton(false);
	pThis->m_pMapSystem->resetMap();
}
