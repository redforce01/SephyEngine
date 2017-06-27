#include "stdafx.h"
#include "control_SaveButton.h"
#include "mapSystem.h"

Control_SaveButton::Control_SaveButton()
{
	m_pMapSystem = nullptr;
}


Control_SaveButton::~Control_SaveButton()
{
	SAFE_DELETE(m_pIcon);
}

bool Control_SaveButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionSave, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, 26, 28, 0, IMAGEMANAGER->getTexture("SaveButton"));
		m_dxFont.initialize(g, saveButtonNS::FONT_HEIGHT, false, false, saveButtonNS::FONT);
		m_dxFont.setFontColor(saveButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(saveButtonNS::name);

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
	MessageBox(g_hWndEngine, "TestFunction", "Test", MB_OK);
}
