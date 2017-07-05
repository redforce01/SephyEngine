#include "stdafx.h"
#include "control_LoadButton.h"
#include "logViewer.h"
#include "mapSystem.h"

Control_LoadButton::Control_LoadButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_LoadButton::~Control_LoadButton()
{
}

bool Control_LoadButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionLoad, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, loadButtonNS::IMAGE_WIDTH, loadButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(loadButtonNS::FILENAME));
		m_dxFont.initialize(g, loadButtonNS::FONT_HEIGHT, false, false, loadButtonNS::FONT);
		m_dxFont.setFontColor(loadButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(loadButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "LOAD Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_LoadButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_LoadButton::render()
{
	SystemUIButton::render();
}

void Control_LoadButton::functionLoad(void * obj)
{
	Control_LoadButton* pThis = (Control_LoadButton*)obj;
	pThis->m_pInput->setMouseLButton(false);
	pThis->m_pMapSystem->loadData();
	pThis->m_pLogViewer->addLog("Map Load Called");
}
