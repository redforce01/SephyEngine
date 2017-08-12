#include "stdafx.h"
#include "control_DebugObjectButton.h"
#include "mapSystem.h"
#include "logViewer.h"

Control_DebugObjectButton::Control_DebugObjectButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}

Control_DebugObjectButton::~Control_DebugObjectButton()
{
}

bool Control_DebugObjectButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionDebugObject, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, debugObjectButtonNS::IMAGE_WIDTH, debugObjectButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(debugObjectButtonNS::FILENAME));
		m_dxFont.initialize(g, debugObjectButtonNS::FONT_HEIGHT, false, false, debugObjectButtonNS::FONT);
		m_dxFont.setFontColor(debugObjectButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(debugObjectButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_DebugObjectButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_DebugObjectButton::render()
{
	SystemUIButton::render();
}

void Control_DebugObjectButton::functionDebugObject(void * obj)
{
	Control_DebugObjectButton* pThis = (Control_DebugObjectButton*)obj;
	pThis->m_pInput->setMouseLButton(false);


	pThis->m_pMapSystem->setDebugObject();
	if (pThis->m_pMapSystem->getDebugObject() == true)
		pThis->m_pLogViewer->addLog(debugObjectButtonNS::LOG_ON);
	else
		pThis->m_pLogViewer->addLog(debugObjectButtonNS::LOG_OFF);
}