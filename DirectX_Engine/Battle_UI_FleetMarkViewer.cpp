#include "stdafx.h"
#include "Battle_UI_FleetMarkViewer.h"


CBattle_UI_FleetMarkViewer::CBattle_UI_FleetMarkViewer()
{
	backColor = battleFleetMarkViewerNS::BACK_COLOR_ACTIVE;
	m_bVisibleView	= true;
	m_bAnime		= false;
}


CBattle_UI_FleetMarkViewer::~CBattle_UI_FleetMarkViewer()
{
	for (auto iter : m_vFleetMarks)
	{
		SAFE_DELETE(iter);
	}
}

bool CBattle_UI_FleetMarkViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		for (int k = 0; k < battleFleetMarkViewerNS::FLEET_MARK_MAX_COUNT; k++)
		{
			CBattle_UI_FleetMark* temp = new CBattle_UI_FleetMark;
			temp->initialize(g, i, k);
			m_vFleetMarks.emplace_back(temp);
		}

		success = SystemUIDialog::initializeDialog(g, i,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_X,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_Y,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_WIDTH,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_HEIGHT, 0);
		SystemUIDialog::setDrawBorder(false);

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFleetMarkViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetMarkViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	//if (PtInRect(&this->getDialogRECT(), m_pInput->getMousePt()))
	//{
	//	m_bVisibleView = true;
	//}
	//else
	//{
	//	m_bVisibleView = false;
	//}

	//if (m_bVisibleView)
	//{
	//	if (this->getDialogX() < battleFleetMarkViewerNS::FLEET_MARK_VIEW_X)
	//	{
	//		SystemUIDialog::moveDialogX(battleFleetMarkViewerNS::FLEET_ANIME_SPEED * frameTime);
	//		for (auto iter : m_vFleetMarks)
	//		{
	//			iter->moveFleetMarkX(battleFleetMarkViewerNS::FLEET_ANIME_SPEED * frameTime);
	//		}
	//	}		
	//}
	//else
	//{
	//	if (this->getDialogX() > battleFleetMarkViewerNS::FLEET_MARK_INVISIBLE_X)
	//	{
	//		SystemUIDialog::moveDialogX(-battleFleetMarkViewerNS::FLEET_ANIME_SPEED * frameTime);
	//		for (auto iter : m_vFleetMarks)
	//		{
	//			iter->moveFleetMarkX(-battleFleetMarkViewerNS::FLEET_ANIME_SPEED * frameTime);
	//		}
	//	}
	//}

	if (SystemUIDialog::getMouseOver() == false)
		return;

	for (auto iter : m_vFleetMarks)
	{
		iter->update(frameTime);
	}
}

void CBattle_UI_FleetMarkViewer::render()
{
	SystemUIDialog::render();
	

	for (auto iter : m_vFleetMarks)
	{
		iter->render();
	}
}