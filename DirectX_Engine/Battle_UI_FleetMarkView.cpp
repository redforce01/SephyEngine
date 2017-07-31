#include "stdafx.h"
#include "Battle_UI_FleetMarkView.h"


CBattle_UI_FleetMarkView::CBattle_UI_FleetMarkView()
{
	backColor = battleFleetMarkViewNS::BACK_COLOR_ACTIVE;
}


CBattle_UI_FleetMarkView::~CBattle_UI_FleetMarkView()
{
	for (auto iter : m_vFleetMarks)
	{
		SAFE_DELETE(iter);
	}
}

bool CBattle_UI_FleetMarkView::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		for (int k = 0; k < battleFleetMarkViewNS::FLEET_MARK_MAX_COUNT; k++)
		{
			CBattle_UI_FleetMark* temp = new CBattle_UI_FleetMark;
			temp->initialize(g, i, k);
			m_vFleetMarks.emplace_back(temp);
		}

		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - battleFleetMarkViewNS::FLEET_MARK_VIEW_WIDTH,
			battleFleetMarkViewNS::FLEET_MARK_VIEW_Y,
			battleFleetMarkViewNS::FLEET_MARK_VIEW_WIDTH,
			battleFleetMarkViewNS::FLEET_MARK_VIEW_HEIGHT, 0);
		SystemUIDialog::setDrawBorder(false);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFleetMarkViewNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetMarkView::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (SystemUIDialog::getMouseOver() == false)
		return;

	for (auto iter : m_vFleetMarks)
	{
		iter->update(frameTime);
	}
}

void CBattle_UI_FleetMarkView::render()
{
	SystemUIDialog::render();

	for (auto iter : m_vFleetMarks)
	{
		iter->render();
	}
}
