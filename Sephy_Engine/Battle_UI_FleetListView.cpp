#include "stdafx.h"
#include "Battle_UI_FleetListView.h"
#include "Battle_UnitSystem.h"

CBattle_UI_FleetListView* pThis = nullptr;
CBattle_UI_FleetListView::CBattle_UI_FleetListView() : SystemUIDialog()
{
	::pThis = this;
	//=================================================
	m_pBattleUnitSystem = nullptr;
	m_pGraphics			= nullptr;
	m_pInput			= nullptr;
	//=================================================
	m_pFleetButton		= nullptr;
	m_pSendButton		= nullptr;
	m_pClearButton		= nullptr;
	m_pCloseButton		= nullptr;
	//=================================================
	m_pPageUpButton		= nullptr;
	m_pPageDownButton	= nullptr;
	m_nItemStart		= 0;
	m_nItemEnd			= 0;
	//=================================================
	m_nSelectItemPhase	= -1;
	m_nSelectItemCount	= -1;
	m_nSelectItemNumber = -1;
	m_rcGuideShipType	= { 0, };
	m_rcGuideShipName	= { 0, };
	m_rcGuideShipPhase	= { 0, };
	m_rcGuideShipCount	= { 0, };
	//=================================================
	m_x					= battleFleetListViewNS::FLEET_BUTTON_X;
	m_y					= battleFleetListViewNS::FLEET_BUTTON_Y;
	m_width				= battleFleetListViewNS::FLEET_VIEW_INACTIVE_WIDTH;
	m_height			= battleFleetListViewNS::FLEET_VIEW_INACTIVE_HEIGHT;
	//=================================================
	m_bInitialized		= false;
	m_bActive			= false;
	m_bVisible			= true;
	//=================================================
	m_strGuideShipType	= battleFleetListViewNS::FLEET_LIST_GUIDE_SHIPTYPE;
	m_strGuideShipName	= battleFleetListViewNS::FLEET_LIST_GUIDE_SHIPNAME;
	m_strGuideShipPhase = battleFleetListViewNS::FLEET_LIST_GUIDE_SHIPPHASE;
	m_strGuideShipCount = battleFleetListViewNS::FLEET_LIST_GUIDE_SHIPCOUNT;
	//=================================================
	backColor			= battleFleetListViewNS::BACK_COLOR_ACTIVE;
}


CBattle_UI_FleetListView::~CBattle_UI_FleetListView()
{
	SAFE_DELETE(m_pFleetButton);
	SAFE_DELETE(m_pSendButton);
	SAFE_DELETE(m_pClearButton);
	SAFE_DELETE(m_pCloseButton);
	SAFE_DELETE(m_pPageUpButton);
	SAFE_DELETE(m_pPageDownButton);
}

bool CBattle_UI_FleetListView::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(g, i, m_x, m_y, m_width, m_height, 0);
		SystemUIDialog::setDrawBorder(false);

		success = m_dxFont.initialize(g, battleFleetListViewNS::FONT_HEIGHT, false, false, battleFleetListViewNS::FONT);
		//==========================================================================================================
		m_pFleetButton = new SystemButton;
		m_pFleetButton->initialize(m_pGraphics, m_pInput,
			battleFleetListViewNS::FLEET_BUTTON_X,
			battleFleetListViewNS::FLEET_BUTTON_Y,
			battleFleetListViewNS::FLEET_BUTTON_FILENAME, false);
		m_pFleetButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionFleetButton));

		m_pSendButton = new SystemButton;
		m_pSendButton->initialize(m_pGraphics, m_pInput,
			battleFleetListViewNS::SEND_BUTTON_X,
			battleFleetListViewNS::SEND_BUTTON_Y,
			battleFleetListViewNS::SEND_BUTTON_FILENAME, true);
		m_pSendButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionSendButton));

		m_pClearButton = new SystemButton;
		m_pClearButton->initialize(m_pGraphics, m_pInput,
			battleFleetListViewNS::CLEAR_BUTTON_X,
			battleFleetListViewNS::CLEAR_BUTTON_Y,
			battleFleetListViewNS::CLEAR_BUTTON_FILENAME, true);
		m_pClearButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionClearButton));

		m_pCloseButton = new SystemButton;
		m_pCloseButton->initialize(m_pGraphics, m_pInput,
			battleFleetListViewNS::CLOSE_BUTTON_X,
			battleFleetListViewNS::CLOSE_BUTTON_Y,
			battleFleetListViewNS::CLOSE_BUTTON_FILENAME, true);
		m_pCloseButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionCloseButton));

		m_pPageUpButton = new SystemButton;
		m_pPageUpButton->initialize(m_pGraphics, m_pInput,
			this->getDialogX() + this->getDialogWidth() + battleFleetListViewNS::PAGE_UP_BUTTON_RELATE_X,
			this->getDialogY() + this->getDialogHeight() + battleFleetListViewNS::PAGE_UP_BUTTON_RELATE_Y,
			battleFleetListViewNS::PAGE_UP_BUTTON_FILENAME, true);
		m_pPageUpButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionPageUpButton));

		m_pPageDownButton = new SystemButton;
		m_pPageDownButton->initialize(m_pGraphics, m_pInput,
			this->getDialogX() + this->getDialogWidth() + battleFleetListViewNS::PAGE_DOWN_BUTTON_RELATE_X,
			this->getDialogY() + this->getDialogHeight() + battleFleetListViewNS::PAGE_DOWN_BUTTON_RELATE_Y,
			battleFleetListViewNS::PAGE_DOWN_BUTTON_FILENAME, true);
		m_pPageDownButton->setRegistFunction(std::bind(&CBattle_UI_FleetListView::functionPageDownButton));
		//==========================================================================================================
		float totalRate = battleFleetListViewNS::FLEET_LIST_GUIDE_NAME_WIDTH_RATE 
			+ battleFleetListViewNS::FLEET_LIST_GUIDE_PHASE_WIDTH_RATE
			+ battleFleetListViewNS::FLEET_LIST_GUIDE_COUNT_WIDTH_RATE
			+ battleFleetListViewNS::FLEET_LIST_GUIDE_TYPE_WIDTH_RATE;

		float guideWidth = battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH * (battleFleetListViewNS::FLEET_LIST_GUIDE_TYPE_WIDTH_RATE / totalRate);
		m_rcGuideShipType = RectMake(battleFleetListViewNS::FLEET_LIST_GUIDE_START_X, battleFleetListViewNS::FLEET_LIST_GUIDE_START_Y,
			battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH * (battleFleetListViewNS::FLEET_LIST_GUIDE_TYPE_WIDTH_RATE / totalRate),
			battleFleetListViewNS::FLEET_LIST_GUIDE_HEIGHT);

		guideWidth = battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH * (battleFleetListViewNS::FLEET_LIST_GUIDE_NAME_WIDTH_RATE / totalRate);
		m_rcGuideShipName = RectMake(m_rcGuideShipType.right, m_rcGuideShipType.top,
			guideWidth,
			battleFleetListViewNS::FLEET_LIST_GUIDE_HEIGHT);

		guideWidth = battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH * (battleFleetListViewNS::FLEET_LIST_GUIDE_PHASE_WIDTH_RATE / totalRate);
		m_rcGuideShipPhase = RectMake(m_rcGuideShipName.right, m_rcGuideShipName.top,
			guideWidth,
			battleFleetListViewNS::FLEET_LIST_GUIDE_HEIGHT);

		guideWidth = battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH * (battleFleetListViewNS::FLEET_LIST_GUIDE_COUNT_WIDTH_RATE / totalRate);
		m_rcGuideShipCount = RectMake(m_rcGuideShipPhase.right, m_rcGuideShipPhase.top,
			guideWidth,
			battleFleetListViewNS::FLEET_LIST_GUIDE_HEIGHT);
		//==========================================================================================================

		m_bInitialized = success;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFleetListViewNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_UI_FleetListView::update(float frameTime)
{
	if (m_bInitialized == false)
		return;
	
	m_pFleetButton->update(frameTime);

	SystemUIDialog::update(frameTime);
	if (m_bActive == false)
		return;

	m_pSendButton->update(frameTime);
	m_pClearButton->update(frameTime);
	m_pCloseButton->update(frameTime);
	m_pPageUpButton->update(frameTime);
	m_pPageDownButton->update(frameTime);

	if (m_pInput->getMouseLButton())
	{
		int count = 0;
		for (auto iter : m_vFleetListItems)
		{
			if (PtInRect(&iter->rcTotal, m_pInput->getMousePt()))
			{
				m_strSelectItemName = iter->shipName;
				m_nSelectItemPhase = iter->shipPhase;
				m_nSelectItemCount = iter->shipCount;
				m_nSelectItemNumber = count;
				break;
			}
			count++;
		}
	}
}

void CBattle_UI_FleetListView::render()
{
	if (m_bInitialized == false)
		return;

	SystemUIDialog::render();
	m_pFleetButton->render();

	if (m_bActive == false)
		return;

	m_pSendButton->render();
	m_pClearButton->render();
	m_pCloseButton->render();
	m_pPageUpButton->render();
	m_pPageDownButton->render();

	m_pGraphics->drawRect(m_rcGuideShipType);
	m_pGraphics->drawRect(m_rcGuideShipName);
	m_pGraphics->drawRect(m_rcGuideShipPhase);
	m_pGraphics->drawRect(m_rcGuideShipCount);

	m_pGraphics->spriteBegin();
	m_dxFont.print(m_strGuideShipType, m_rcGuideShipType, DT_CENTER | DT_VCENTER);
	m_dxFont.print(m_strGuideShipName, m_rcGuideShipName, DT_CENTER | DT_VCENTER);
	m_dxFont.print(m_strGuideShipPhase, m_rcGuideShipPhase, DT_CENTER | DT_VCENTER);
	m_dxFont.print(m_strGuideShipCount, m_rcGuideShipCount, DT_CENTER | DT_VCENTER);

	int count = 0;
	for (auto iter : m_vFleetListItems)
	{
		if (iter->y + iter->height >= m_y + m_height)
			break;

		if (count == m_nSelectItemNumber)
			m_dxFont.setFontColor(graphicsNS::TEAL);
		else
			m_dxFont.setFontColor(graphicsNS::WHITE);

		m_dxFont.print(iter->shipType, iter->rcType, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_dxFont.print(iter->shipName, iter->rcName, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		m_dxFont.print(std::to_string(iter->shipPhase), iter->rcPhase, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_dxFont.print(std::to_string(iter->shipCount), iter->rcCount, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		count++;
	}
	m_dxFont.setFontColor(graphicsNS::WHITE);
	m_pGraphics->spriteEnd();
	
	if (m_nSelectItemNumber >= 0)
	{
		m_pGraphics->drawRect(m_vFleetListItems[m_nSelectItemNumber]->rcTotal, 1.3f, graphicsNS::LTGRAY);
	}

}

void CBattle_UI_FleetListView::functionFleetButton()
{
	pThis->m_bActive = !pThis->m_bActive;

	bool bActive = pThis->m_bActive;
	if (bActive)
	{
		// FLEET LIST ACTIVE
		pThis->setDialogBackColor(battleFleetListViewNS::BACK_COLOR_ACTIVE);
		pThis->setDialogPos(battleFleetListViewNS::FLEET_VIEW_X, battleFleetListViewNS::FLEET_VIEW_Y);
		pThis->setDialogWidth(battleFleetListViewNS::FLEET_VIEW_ACTIVE_WIDTH);
		pThis->setDialogHeight(battleFleetListViewNS::FLEET_VIEW_ACTIVE_HEIGHT);
		pThis->setDrawBorder(true);
	}
	else
	{
		// FLEET LIST INACTIVE
		pThis->setDialogBackColor(battleFleetListViewNS::BACK_COLOR_DEACTIVE);
		pThis->setDialogPos(battleFleetListViewNS::FLEET_BUTTON_X, battleFleetListViewNS::FLEET_BUTTON_Y);
		pThis->setDialogWidth(battleFleetListViewNS::FLEET_VIEW_INACTIVE_WIDTH);
		pThis->setDialogHeight(battleFleetListViewNS::FLEET_VIEW_INACTIVE_HEIGHT);
		pThis->setDrawBorder(false);
	}
}

void CBattle_UI_FleetListView::functionSendButton()
{
	if (pThis->m_nSelectItemNumber < 0)
		return;

	std::string shipName = pThis->m_vFleetListItems[pThis->m_nSelectItemNumber]->shipName;
	int shipPhase = pThis->m_vFleetListItems[pThis->m_nSelectItemNumber]->shipPhase;

	int currentBattlePhase = pThis->m_pBattleUnitSystem->getBattlePhase();
	if (shipPhase > currentBattlePhase)
		return;

	if (pThis->m_vFleetListItems[pThis->m_nSelectItemNumber]->shipCount <= 0)
		return;
	
	pThis->m_pBattleUnitSystem->setupShip(shipName);
	pThis->m_vFleetListItems[pThis->m_nSelectItemNumber]->shipCount -= 1;
}

void CBattle_UI_FleetListView::functionClearButton()
{
	pThis->m_pBattleUnitSystem->clearActiveShip();
}

void CBattle_UI_FleetListView::functionCloseButton()
{
	pThis->m_bActive = false;
	pThis->setDialogBackColor(battleFleetListViewNS::BACK_COLOR_DEACTIVE);
	pThis->setDialogPos(battleFleetListViewNS::FLEET_BUTTON_X, battleFleetListViewNS::FLEET_BUTTON_Y);
	pThis->setDialogWidth(battleFleetListViewNS::FLEET_VIEW_INACTIVE_WIDTH);
	pThis->setDialogHeight(battleFleetListViewNS::FLEET_VIEW_INACTIVE_HEIGHT);
	pThis->setDrawBorder(false);
}

void CBattle_UI_FleetListView::functionPageUpButton()
{
	pThis->m_nItemStart++;
	pThis->m_nItemEnd++;	
}

void CBattle_UI_FleetListView::functionPageDownButton()
{
	pThis->m_nItemStart--;
	pThis->m_nItemEnd--;
}

void CBattle_UI_FleetListView::addShipToFleetList(std::string strShipType, std::string strShipName, int nPhase)
{
	for (auto iter : m_vFleetListItems)
	{
		if (iter->shipName.compare(strShipName) == false)
		{
			iter->shipCount++;
			return;
		}
	}

	tagFleetItem* tempItem = new tagFleetItem(strShipType, strShipName, nPhase);
	if (m_vFleetListItems.size() > 0)
	{
		auto lastItem = m_vFleetListItems.size() - 1;

		float x = tempItem->x = battleFleetListViewNS::FLEET_LIST_ITEM_START_X;
		float y = tempItem->y = m_vFleetListItems[lastItem]->y + battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT;
		float width = tempItem->width = battleFleetListViewNS::FLEET_LIST_ITEM_WIDTH;
		float height = tempItem->height = battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT;
		tempItem->rcType = RectMake(x, y,
			(m_rcGuideShipType.right - m_rcGuideShipType.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcName = RectMake(tempItem->rcType.right, tempItem->rcType.top,
			(m_rcGuideShipName.right - m_rcGuideShipName.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcPhase = RectMake(tempItem->rcName.right, tempItem->rcName.top,
			(m_rcGuideShipPhase.right - m_rcGuideShipPhase.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcCount = RectMake(tempItem->rcPhase.right, tempItem->rcPhase.top,
			(m_rcGuideShipCount.right - m_rcGuideShipCount.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcTotal = RectMake(tempItem->rcType.left, tempItem->rcType.top,
			tempItem->rcCount.right - tempItem->rcType.left,
			tempItem->rcCount.bottom - tempItem->rcType.top);
	}
	else
	{		
		float x = tempItem->x = battleFleetListViewNS::FLEET_LIST_ITEM_START_X;
		float y = tempItem->y = battleFleetListViewNS::FLEET_LIST_ITEM_START_Y;
		float width = tempItem->width = battleFleetListViewNS::FLEET_LIST_ITEM_WIDTH;
		float height = tempItem->height = battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT;

		tempItem->rcType = RectMake(x, y,
			(m_rcGuideShipType.right - m_rcGuideShipType.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcName = RectMake(tempItem->rcType.right, tempItem->rcType.top,
			(m_rcGuideShipName.right - m_rcGuideShipName.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcPhase = RectMake(tempItem->rcName.right, tempItem->rcName.top,
			(m_rcGuideShipPhase.right - m_rcGuideShipPhase.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcCount = RectMake(tempItem->rcPhase.right, tempItem->rcPhase.top,
			(m_rcGuideShipCount.right - m_rcGuideShipCount.left),
			battleFleetListViewNS::FLEET_LIST_ITEM_HEIGHT);

		tempItem->rcTotal = RectMake(tempItem->rcType.left, tempItem->rcType.top,
			tempItem->rcCount.right - tempItem->rcType.left,
			tempItem->rcCount.bottom - tempItem->rcType.top);
	}

	m_vFleetListItems.emplace_back(tempItem);
}
