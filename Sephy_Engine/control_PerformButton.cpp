#include "stdafx.h"
#include "control_PerformButton.h"
#include "statsViewer.h"
#include "logViewer.h"

Control_PerformButton::Control_PerformButton()
{
	m_pStatsViewer = nullptr;
	m_pLogViewer = nullptr;
}


Control_PerformButton::~Control_PerformButton()
{
}

bool Control_PerformButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionPerform, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, performButtonNS::IMAGE_WIDTH, performButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(performButtonNS::FILENAME));
		m_dxFont.initialize(g, performButtonNS::FONT_HEIGHT, false, false, performButtonNS::FONT);
		m_dxFont.setFontColor(performButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(performButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Performance Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_PerformButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_PerformButton::render()
{
	SystemUIButton::render();
}

void Control_PerformButton::functionPerform(void * obj)
{
	Control_PerformButton* pThis = (Control_PerformButton*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_pStatsViewer->setShowHide();
	if(pThis->m_pStatsViewer->getVisible())
		pThis->m_pLogViewer->addLog("Performance Viewer On");
	else 
		pThis->m_pLogViewer->addLog("Performance Viewer Off");
}
