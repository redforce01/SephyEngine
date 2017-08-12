#include "stdafx.h"
#include "control_DebugCellButton.h"
#include "mapSystem.h"
#include "logViewer.h"

Control_DebugCellButton::Control_DebugCellButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_DebugCellButton::~Control_DebugCellButton()
{
}

bool Control_DebugCellButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionDebugCell, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, debugcellButtonNS::IMAGE_WIDTH, debugcellButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(debugcellButtonNS::FILENAME));
		m_dxFont.initialize(g, debugcellButtonNS::FONT_HEIGHT, false, false, debugcellButtonNS::FONT);
		m_dxFont.setFontColor(debugcellButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(debugcellButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Cell Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_DebugCellButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_DebugCellButton::render()
{
	SystemUIButton::render();
}

void Control_DebugCellButton::functionDebugCell(void * obj)
{
	Control_DebugCellButton* pThis = (Control_DebugCellButton*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_pMapSystem->setDebugTile();
	if (pThis->m_pMapSystem->getDebugTile() == true)
		pThis->m_pLogViewer->addLog(debugcellButtonNS::LOG_ON);
	else
		pThis->m_pLogViewer->addLog(debugcellButtonNS::LOG_OFF);
}
