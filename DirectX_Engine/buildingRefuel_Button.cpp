#include "stdafx.h"
#include "buildingRefuel_Button.h"
#include "mapSystem.h"

BuildingRefuel_Button::BuildingRefuel_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


BuildingRefuel_Button::~BuildingRefuel_Button()
{
}

bool BuildingRefuel_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionBuildingRefuel, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, buildingRefuelButtonNS::FONT_HEIGHT, false, false, buildingRefuelButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(buildingRefuelButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(buildingRefuelButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void BuildingRefuel_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void BuildingRefuel_Button::render()
{
	SystemUIButton::render();
}

void BuildingRefuel_Button::functionBuildingRefuel(void * obj)
{
	BuildingRefuel_Button* pThis = (BuildingRefuel_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(buildingRefuelButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(buildingRefuelButtonNS::FONT_COLOR_INACTIVE);
	}
}
