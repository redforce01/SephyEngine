#include "stdafx.h"
#include "control_DebugEventObjButton.h"
#include "mapSystem.h"
#include "logViewer.h"

Control_DebugEventObjButton::Control_DebugEventObjButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_DebugEventObjButton::~Control_DebugEventObjButton()
{
}

bool Control_DebugEventObjButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionDebugEventObject, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, debugEventObjectButtonNS::IMAGE_WIDTH, debugEventObjectButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(debugEventObjectButtonNS::FILENAME));
		m_dxFont.initialize(g, debugEventObjectButtonNS::FONT_HEIGHT, false, false, debugEventObjectButtonNS::FONT);
		m_dxFont.setFontColor(debugEventObjectButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(debugEventObjectButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Cell Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_DebugEventObjButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_DebugEventObjButton::render()
{
	SystemUIButton::render();
}

void Control_DebugEventObjButton::functionDebugEventObject(void * obj)
{
	Control_DebugEventObjButton* pThis = (Control_DebugEventObjButton*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_pMapSystem->setDebugEventObject();
	if (pThis->m_pMapSystem->getDebugEventObject() == true)
		pThis->m_pLogViewer->addLog(debugEventObjectButtonNS::LOG_ON);
	else
		pThis->m_pLogViewer->addLog(debugEventObjectButtonNS::LOG_OFF);
}
