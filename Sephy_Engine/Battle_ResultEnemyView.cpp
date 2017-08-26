#include "stdafx.h"
#include "Battle_ResultEnemyView.h"


CBattle_ResultEnemyView::CBattle_ResultEnemyView()
{
	backColor = battleResultEnemyViewNS::BACK_COLOR;
	m_rcShipNameGuide = { 0, };
	m_rcShipNumberGuide = { 0, };
	m_rcViewTitle = { 0, };
	m_strViewTitle = battleResultEnemyViewNS::VIEW_GUIDE_TITLE_PLAYER;
	m_strScore = "0";
}


CBattle_ResultEnemyView::~CBattle_ResultEnemyView()
{
	for (auto iter : m_vListItem)
	{
		SAFE_DELETE(iter);
	}
	m_vListItem.clear();
}

bool CBattle_ResultEnemyView::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
			g_fScreenWidth + battleResultEnemyViewNS::VIEW_RELATE_X - battleResultEnemyViewNS::VIEW_WIDTH,
			(g_fScreenHeight / 2) + battleResultEnemyViewNS::VIEW_RELATE_Y,
			battleResultEnemyViewNS::VIEW_WIDTH,
			battleResultEnemyViewNS::VIEW_HEIGHT);
		m_dxFont.initialize(m_pGraphics, battleResultEnemyViewNS::FONT_HEIGHT, false, false, battleResultEnemyViewNS::FONT);
		m_rcViewTitle = RectMake(
			this->getDialogX() + battleResultEnemyViewNS::VIEW_GUIDE_TITLE_PLAYER_RELATE_X,
			this->getDialogY() + battleResultEnemyViewNS::VIEW_GUIDE_TITLE_PLAYER_RELATE_Y,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_PLAYER_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_PLAYER_HEIGHT);

		m_rcScoreTitle = RectMake(
			this->getDialogX() + battleResultEnemyViewNS::DAMAGE_SCORE_TITLE_RELATE_X,
			this->getDialogY() + battleResultEnemyViewNS::DAMAGE_SCORE_TITLE_RELATE_Y,
			battleResultEnemyViewNS::DAMAGE_SCORE_TITLE_WIDTH,
			battleResultEnemyViewNS::DAMAGE_SCORE_TITLE_HEIGHT);
		m_rcScore = RectMake(
			this->getDialogX() + battleResultEnemyViewNS::VIEW_GUIDE_SCORE_BOX_RELATE_X,
			this->getDialogY() + battleResultEnemyViewNS::VIEW_GUIDE_SCORE_BOX_RELATE_Y,
			battleResultEnemyViewNS::VIEW_GUIDE_SCORE_BOX_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_SCORE_BOX_HEIGHT);

		m_rcShipNumberGuide = RectMake(
			this->getDialogX() + battleResultEnemyViewNS::VIEW_GUIDE_START_RELATE_X,
			this->getDialogY() + battleResultEnemyViewNS::VIEW_GUIDE_START_RELATE_Y,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		m_rcShipNameGuide = RectMake(
			m_rcShipNumberGuide.right,
			m_rcShipNumberGuide.top,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleResultEnemyViewNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_ResultEnemyView::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);
}

void CBattle_ResultEnemyView::render()
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
	m_dxFont.print(battleResultEnemyViewNS::DAMAGE_SCORE_TITLE, m_rcScoreTitle, DT_CENTER | DT_VCENTER);
	m_dxFont.print(battleResultEnemyViewNS::VIEW_GUIDE_TITLE_SHIP, m_rcShipNameGuide, DT_CENTER | DT_VCENTER);
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

void CBattle_ResultEnemyView::addListItem(std::string shipName)
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
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		newItem->rcName = RectMake(
			m_vListItem[lastItem]->rcName.left,
			m_vListItem[lastItem]->rcName.bottom,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
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
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_NUMBER_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		newItem->rcName = RectMake(
			m_rcShipNameGuide.left,
			m_rcShipNameGuide.bottom,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_SHIPNAME_WIDTH,
			battleResultEnemyViewNS::VIEW_GUIDE_TITLE_HEIGHT);
		m_vListItem.emplace_back(newItem);
	}
}
