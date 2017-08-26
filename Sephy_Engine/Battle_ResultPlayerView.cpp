#include "stdafx.h"
#include "Battle_ResultPlayerView.h"


CBattle_ResultPlayerView::CBattle_ResultPlayerView()
{
	backColor = battleResultPlayerViewNS::BACK_COLOR;
	m_rcShipNameGuide	= { 0, };
	m_rcShipNumberGuide = { 0, };
	m_rcViewTitle		= { 0, };
	m_strViewTitle		= battleResultPlayerViewNS::VIEW_GUIDE_TITLE_PLAYER;
}


CBattle_ResultPlayerView::~CBattle_ResultPlayerView()
{
	for (auto iter : m_vListItem)
	{
		SAFE_DELETE(iter);
	}
	m_vListItem.clear();
}

bool CBattle_ResultPlayerView::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
			battleResultPlayerViewNS::VIEW_RELATE_X,
			(g_fScreenHeight/2) + battleResultPlayerViewNS::VIEW_RELATE_Y,
			battleResultPlayerViewNS::VIEW_WIDTH,
			battleResultPlayerViewNS::VIEW_HEIGHT);
		m_dxFont.initialize(m_pGraphics, battleResultPlayerViewNS::FONT_HEIGHT, false, false, battleResultPlayerViewNS::FONT);
		m_rcViewTitle = RectMake(
			this->getDialogX() + battleResultPlayerViewNS::VIEW_GUIDE_TITLE_PLAYER_RELATE_X,
			this->getDialogY() + battleResultPlayerViewNS::VIEW_GUIDE_TITLE_PLAYER_RELATE_Y,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_PLAYER_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_PLAYER_HEIGHT);

		m_rcScoreTitle = RectMake(
			this->getDialogX() + battleResultPlayerViewNS::DAMAGE_SCORE_TITLE_RELATE_X,
			this->getDialogY() + battleResultPlayerViewNS::DAMAGE_SCORE_TITLE_RELATE_Y,
			battleResultPlayerViewNS::DAMAGE_SCORE_TITLE_WIDTH,
			battleResultPlayerViewNS::DAMAGE_SCORE_TITLE_HEIGHT);
		m_rcScore = RectMake(
			this->getDialogX() + battleResultPlayerViewNS::VIEW_GUIDE_SCORE_BOX_RELATE_X,
			this->getDialogY() + battleResultPlayerViewNS::VIEW_GUIDE_SCORE_BOX_RELATE_Y,
			battleResultPlayerViewNS::VIEW_GUIDE_SCORE_BOX_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_SCORE_BOX_HEIGHT);

		m_rcShipNumberGuide = RectMake(
			this->getDialogX() + battleResultPlayerViewNS::VIEW_GUIDE_START_RELATE_X,
			this->getDialogY() + battleResultPlayerViewNS::VIEW_GUIDE_START_RELATE_Y,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		m_rcShipNameGuide = RectMake(
			m_rcShipNumberGuide.right,
			m_rcShipNumberGuide.top,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleResultPlayerViewNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_ResultPlayerView::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);
}

void CBattle_ResultPlayerView::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	auto lastItem = m_vListItem.size() - 1;

	m_pGraphics->drawRect(m_rcScore);
	m_pGraphics->drawRect(m_rcShipNameGuide);
	m_pGraphics->drawRect(m_rcShipNumberGuide);
	m_pGraphics->spriteBegin();
	m_dxFont.print(m_strViewTitle, m_rcViewTitle, DT_CENTER | DT_VCENTER);
	m_dxFont.print(battleResultPlayerViewNS::DAMAGE_SCORE_TITLE, m_rcScoreTitle, DT_CENTER | DT_VCENTER);
	m_dxFont.print(battleResultPlayerViewNS::VIEW_GUIDE_TITLE_SHIP, m_rcShipNameGuide, DT_CENTER | DT_VCENTER);
	RECT rcPrintScore = m_rcScore;
	rcPrintScore.right -= 10;
	m_dxFont.print(m_strScore, rcPrintScore, DT_RIGHT | DT_VCENTER);
	for (auto iter : m_vListItem)
	{ 
		m_pGraphics->drawRect(iter->rcNumber);
		m_pGraphics->drawRect(iter->rcName);
		m_dxFont.print(iter->itemNumber, iter->rcNumber, DT_CENTER | DT_VCENTER);
		m_dxFont.print(iter->shipName, iter->rcName, DT_CENTER | DT_VCENTER);
	}
	m_pGraphics->spriteEnd();
}

void CBattle_ResultPlayerView::addListItem(std::string shipName)
{
	auto itemSize = m_vListItem.size();
	if (itemSize > 0)
	{
		int lastItem = itemSize - 1;
		tagViewItem* newItem = new tagViewItem;
		ZeroMemory(newItem, sizeof(newItem));
		newItem->itemNumber = std::to_string(itemSize + 1);
		newItem->shipName = shipName;
		newItem->rcNumber = RectMake(
			m_vListItem[lastItem]->rcNumber.left,
			m_vListItem[lastItem]->rcNumber.bottom,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		newItem->rcName = RectMake(
			m_vListItem[lastItem]->rcName.left,
			m_vListItem[lastItem]->rcName.bottom,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		m_vListItem.emplace_back(newItem);
	}
	else
	{
		tagViewItem* newItem = new tagViewItem;
		ZeroMemory(newItem, sizeof(newItem));
		newItem->itemNumber = std::to_string(itemSize + 1);
		newItem->shipName = shipName;
		newItem->rcNumber = RectMake(
			m_rcShipNumberGuide.left,
			m_rcShipNumberGuide.bottom,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		newItem->rcName = RectMake(
			m_rcShipNameGuide.left,
			m_rcShipNameGuide.bottom,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultPlayerViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		m_vListItem.emplace_back(newItem);
	}
}