#include "stdafx.h"
#include "buildingObserver_Button.h"
#include "mapSystem.h"

BuildingObserver_Button::BuildingObserver_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


BuildingObserver_Button::~BuildingObserver_Button()
{
}

bool BuildingObserver_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionBuildingObserver, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, buildingObserverButtonNS::FONT_HEIGHT, false, false, buildingObserverButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(buildingObserverButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(buildingObserverButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void BuildingObserver_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void BuildingObserver_Button::render()
{
	SystemUIButton::render();
}

void BuildingObserver_Button::functionBuildingObserver(void * obj)
{
	BuildingObserver_Button* pThis = (BuildingObserver_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_dxFont.setFontColor(buildingObserverButtonNS::FONT_COLOR_ACTIVE);
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(buildingObserverButtonNS::FONT_COLOR_INACTIVE);
	}
}
