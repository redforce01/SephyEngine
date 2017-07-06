#include "stdafx.h"
#include "control_SaveButton.h"
#include "mapSystem.h"
#include "logViewer.h"

Control_SaveButton::Control_SaveButton()
{
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
}


Control_SaveButton::~Control_SaveButton()
{
}

bool Control_SaveButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionSave, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, saveButtonNS::IMAGE_WIDTH, saveButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(saveButtonNS::FILENAME));
		m_dxFont.initialize(g, saveButtonNS::FONT_HEIGHT, false, false, saveButtonNS::FONT);
		m_dxFont.setFontColor(saveButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(saveButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SAVE Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void Control_SaveButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void Control_SaveButton::render()
{
	SystemUIButton::render();
}

void Control_SaveButton::functionSave(void * obj)
{
	Control_SaveButton* pThis = (Control_SaveButton*)obj;	
	pThis->m_pInput->setMouseLButton(false);
	pThis->m_pMapSystem->saveData();
	pThis->m_pLogViewer->addLog("Map Save Called");
}
