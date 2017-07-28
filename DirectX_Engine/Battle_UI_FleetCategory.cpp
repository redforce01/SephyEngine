#include "stdafx.h"
#include "Battle_UI_FleetCategory.h"


CBattle_UI_FleetCategory::CBattle_UI_FleetCategory()
{
	m_pCategoryButton = nullptr;

	m_bVisibleFleetList = false;
}


CBattle_UI_FleetCategory::~CBattle_UI_FleetCategory()
{
	SAFE_DELETE(m_pCategoryButton);
}

bool CBattle_UI_FleetCategory::initialize(Graphics * g, Input* i)
{
	bool success = false;
	try
	{
		m_pCategoryButton = new SystemButton;
		success = m_pCategoryButton->initialize(g, i,
			battleUIFleetCategoryNS::CATEGORY_SHIP_BUTTON_X,
			battleUIFleetCategoryNS::CATEGORY_SHIP_BUTTON_Y,
			battleUIFleetCategoryNS::CATEGORY_SHIP_BUTTON_NAME, true);
		

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Battle UI Fleet Category Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetCategory::update(float frameTime)
{

	m_pCategoryButton->update(frameTime);
}

void CBattle_UI_FleetCategory::render()
{

	m_pCategoryButton->render();
}

void CBattle_UI_FleetCategory::onShowFleetList()
{
	m_bVisibleFleetList = true;



}
