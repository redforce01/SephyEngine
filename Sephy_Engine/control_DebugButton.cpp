#include "stdafx.h"
#include "control_DebugButton.h"
#include "mapSystem.h"
#include "logViewer.h"

Control_DebugButton::Control_DebugButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_DebugButton::~Control_DebugButton()
{
}

bool Control_DebugButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionDebug, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, debugButtonNS::IMAGE_WIDTH, debugButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(debugButtonNS::FILENAME));
		m_dxFont.initialize(g, debugButtonNS::FONT_HEIGHT, false, false, debugButtonNS::FONT);
		m_dxFont.setFontColor(debugButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(debugButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_DebugButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_DebugButton::render()
{
	SystemUIButton::render();
}

void Control_DebugButton::functionDebug(void * obj)
{
	Control_DebugButton* pThis = (Control_DebugButton*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_pMapSystem->setDebug();
	if(pThis->m_pMapSystem->getDebug() == true)
		pThis->m_pLogViewer->addLog(debugButtonNS::LOG_ON);
	else 
		pThis->m_pLogViewer->addLog(debugButtonNS::LOG_OFF);
}
