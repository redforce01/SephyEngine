#include "stdafx.h"
#include "Battle_UI_FleetMarkViewer.h"


CBattle_UI_FleetMarkViewer::CBattle_UI_FleetMarkViewer()
{
	m_pArrow			= nullptr;
	//=======================================
	m_bVisibleView		= true;
	m_bAnime			= false;
	m_nSelectedFleet	= 0;
	//=======================================
	backColor = battleFleetMarkViewerNS::BACK_COLOR_ACTIVE;
}


CBattle_UI_FleetMarkViewer::~CBattle_UI_FleetMarkViewer()
{
	for (auto iter : m_vFleetMarks)
	{
		SAFE_DELETE(iter);
	}
	m_vFleetMarks.clear();
	SAFE_DELETE(m_pArrow);
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
			temp->setMemoryLinkBattleUIFleetMarkViewer(this);
			m_vFleetMarks.emplace_back(temp);
		}

		success = SystemUIDialog::initializeDialog(g, i,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_X,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_Y,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_WIDTH,
			battleFleetMarkViewerNS::FLEET_MARK_VIEW_HEIGHT, 0);
		SystemUIDialog::setDrawBorder(false);

		m_pArrow = new Image;
		m_pArrow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleFleetMarkViewerNS::ARROW_FILENAME));

		float markRight = m_vFleetMarks[0]->getFleetMarkRect().right;
		float markCenterHeight = m_vFleetMarks[0]->getFleetMarkRect().top + (m_vFleetMarks[0]->getHeight() / 2);
		m_pArrow->setX(markRight + 2);
		m_pArrow->setY(markCenterHeight - (m_pArrow->getHeight() / 2));
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

#pragma region FLEET_LIST_VIEW_ANIMATION_NOT USING THIS_CODE
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
#pragma endregion
	
	if (SystemUIDialog::getMouseOver() == false)
		return;

	
	if (m_pInput->getMouseLButton())
	{

	}
	
	
	
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

	m_pGraphics->spriteBegin();
	m_pArrow->draw();
	m_pGraphics->spriteEnd();
}