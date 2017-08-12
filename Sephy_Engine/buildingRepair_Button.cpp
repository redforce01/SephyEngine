#include "stdafx.h"
#include "buildingRepair_Button.h"
#include "mapSystem.h"

BuildingRepair_Button::BuildingRepair_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


BuildingRepair_Button::~BuildingRepair_Button()
{
}

bool BuildingRepair_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionBuildingRepair, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, buildingRepairButtonNS::FONT_HEIGHT, false, false, buildingRepairButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(buildingRepairButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(buildingRepairButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void BuildingRepair_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void BuildingRepair_Button::render()
{
	SystemUIButton::render();
}

void BuildingRepair_Button::functionBuildingRepair(void * obj)
{
	BuildingRepair_Button* pThis = (BuildingRepair_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(buildingRepairButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(buildingRepairButtonNS::FONT_COLOR_INACTIVE);
	}
}
