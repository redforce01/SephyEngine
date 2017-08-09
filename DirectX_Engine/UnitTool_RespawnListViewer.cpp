#include "stdafx.h"
#include "UnitTool_RespawnListViewer.h"
#include "UnitTool_UnitControlSystem.h"

CUnitTool_RespawnListViewer::CUnitTool_RespawnListViewer()
{
	backColor = unitToolRespawnListViewerNs::BACK_COLOR;
	m_rcComputerInfoRect = { 0, };
	m_rcPlayerInfoRect = { 0, };
}


CUnitTool_RespawnListViewer::~CUnitTool_RespawnListViewer()
{
}

bool CUnitTool_RespawnListViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i,
			unitToolRespawnListViewerNs::VIEWER_X,
			unitToolRespawnListViewerNs::VIEWER_Y,
			unitToolRespawnListViewerNs::VIEWER_WIDTH,
			unitToolRespawnListViewerNs::VIEWER_HEIGHT, 0);
		
		m_dxFont.initialize(m_pGraphics, unitToolRespawnListViewerNs::FONT_HEIGHT, false, false, unitToolRespawnListViewerNs::FONT);

		m_rcPlayerInfoRect = RectMake(
			this->getDialogX() + unitToolRespawnListViewerNs::PLAYER_LIST_BOX_RELATE_X,
			this->getDialogY() + unitToolRespawnListViewerNs::PLAYER_LIST_BOX_RELATE_Y,
			unitToolRespawnListViewerNs::LIST_BOX_WIDTH,
			unitToolRespawnListViewerNs::LIST_BOX_HEIGHT);
		m_rcComputerInfoRect = RectMake(
			this->getDialogX() + unitToolRespawnListViewerNs::COMPUTER_LIST_BOX_RELATE_X,
			this->getDialogY() + unitToolRespawnListViewerNs::COMPUTER_LIST_BOX_RELATE_Y,
			unitToolRespawnListViewerNs::LIST_BOX_WIDTH,
			unitToolRespawnListViewerNs::LIST_BOX_HEIGHT);

		m_rcPlayerInfoTitle = RectMake(
			this->getDialogX() + unitToolRespawnListViewerNs::PLAYER_LIST_TITLE_RECT_X,
			this->getDialogY() + unitToolRespawnListViewerNs::PLAYER_LIST_TITLE_RECT_Y,
			unitToolRespawnListViewerNs::LIST_TITLE_WIDTH,
			unitToolRespawnListViewerNs::LIST_TITLE_HEIGHT);

		m_rcComputerInfoTitle = RectMake(
			this->getDialogX() + unitToolRespawnListViewerNs::COMPUTER_LIST_TITLE_RECT_X,
			this->getDialogY() + unitToolRespawnListViewerNs::COMPUTER_LIST_TITLE_RECT_Y,
			unitToolRespawnListViewerNs::LIST_TITLE_WIDTH,
			unitToolRespawnListViewerNs::LIST_TITLE_HEIGHT);
	}
	catch (const std::exception&)
	{
		MessageBox(g_hWndEngine, unitToolRespawnListViewerNs::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CUnitTool_RespawnListViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);


}

void CUnitTool_RespawnListViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->drawRect(m_rcPlayerInfoRect);
	m_pGraphics->drawRect(m_rcComputerInfoRect);
	m_pGraphics->spriteBegin();
	m_dxFont.print(unitToolRespawnListViewerNs::PLAYER_LIST_TITLE, m_rcPlayerInfoTitle, DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolRespawnListViewerNs::COMPUTER_LIST_TITLE, m_rcComputerInfoTitle, DT_LEFT | DT_VCENTER);

	RECT rcTagNumber = RectMake(m_rcPlayerInfoRect.left, m_rcPlayerInfoRect.top,
		unitToolRespawnListViewerNs::ITEM_BOX_TAG_NUMBER_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	RECT rcShipType = RectMake(rcTagNumber.right, rcTagNumber.top,
		unitToolRespawnListViewerNs::ITEM_BOX_SHIP_TYPE_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	RECT rcShipName = RectMake(rcShipType.right, rcShipType.top,
		unitToolRespawnListViewerNs::ITEM_BOX_SHIP_NAME_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	m_dxFont.setFontColor(unitToolRespawnListViewerNs::PLAYER_LIST_COLOR);
	for (auto iter : m_vPlayerUnitList)
	{
		m_pGraphics->drawRect(rcTagNumber);
		m_pGraphics->drawRect(rcShipType);
		m_pGraphics->drawRect(rcShipName);

		m_dxFont.print(std::to_string(iter.tagNumber), rcTagNumber, DT_CENTER | DT_VCENTER);
		m_dxFont.print(iter.shipType, rcShipType, DT_CENTER | DT_VCENTER);
		m_dxFont.print(iter.shipName, rcShipName, DT_CENTER | DT_VCENTER);

		rcTagNumber.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcTagNumber.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipType.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipType.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipName.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipName.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;

		if (rcTagNumber.bottom > m_rcPlayerInfoRect.bottom)
			break;
	}

	rcTagNumber = RectMake(m_rcComputerInfoRect.left, m_rcComputerInfoRect.top,
		unitToolRespawnListViewerNs::ITEM_BOX_TAG_NUMBER_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	rcShipType = RectMake(rcTagNumber.right, rcTagNumber.top,
		unitToolRespawnListViewerNs::ITEM_BOX_SHIP_TYPE_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	rcShipName = RectMake(rcShipType.right, rcShipType.top,
		unitToolRespawnListViewerNs::ITEM_BOX_SHIP_NAME_RELATE_WIDTH,
		unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT);

	m_dxFont.setFontColor(unitToolRespawnListViewerNs::COMPUTER_LIST_COLOR);
	for (auto iter : m_vComputerUnitList)
	{
		m_pGraphics->drawRect(rcTagNumber);
		m_pGraphics->drawRect(rcShipType);
		m_pGraphics->drawRect(rcShipName);

		m_dxFont.print(std::to_string(iter.tagNumber), rcTagNumber, DT_CENTER | DT_VCENTER);
		m_dxFont.print(iter.shipType, rcShipType, DT_CENTER | DT_VCENTER);
		m_dxFont.print(iter.shipName, rcShipName, DT_CENTER | DT_VCENTER);

		rcTagNumber.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcTagNumber.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipType.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipType.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipName.top += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;
		rcShipName.bottom += unitToolRespawnListViewerNs::ITEM_BOX_HEIGHT;

		if (rcTagNumber.bottom > m_rcComputerInfoRect.bottom)
			break;
	}
	m_dxFont.setFontColor(unitToolRespawnListViewerNs::FONT_COLOR);
	m_pGraphics->spriteEnd();
}
