#include "stdafx.h"
#include "UnitTool_UnitMakeViewer.h"
#include "UnitTool_ShipDataSetter.h"

CUnitTool_UnitMakeViewer* pThis = nullptr;
CUnitTool_UnitMakeViewer::CUnitTool_UnitMakeViewer()
{
	m_pUnitToolShipDataSetter = nullptr;
	backColor = unitToolUnitMakeViewerNS::BACK_COLOR;
	m_nSelectNumber = -1;
	::pThis = this;
}


CUnitTool_UnitMakeViewer::~CUnitTool_UnitMakeViewer()
{
}

bool CUnitTool_UnitMakeViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(g, i,
			unitToolUnitMakeViewerNS::VIEWER_RELATE_X,
			unitToolUnitMakeViewerNS::VIEWER_RELATE_Y,
			unitToolUnitMakeViewerNS::VIEWER_WIDTH,
			unitToolUnitMakeViewerNS::VIEWER_HEIGHT, 0);

		success = m_dxFont.initialize(m_pGraphics, unitToolUnitMakeViewerNS::FONT_HEIGHT, false, false, unitToolUnitMakeViewerNS::FONT);

		auto vData = m_unitParser.loadShipList();
		setupShipList(vData);

		float boxX = unitToolUnitMakeViewerNS::LIST_ITEM_BOX_START_X;
		float boxY = unitToolUnitMakeViewerNS::LIST_ITEM_BOX_START_Y;
		float boxWidth = unitToolUnitMakeViewerNS::LIST_ITEM_BOX_WIDTH;
		float boxHeight = unitToolUnitMakeViewerNS::LIST_ITEM_BOX_HEIGHT;

		int boxCount = 0;
		for (auto iter : m_vShipList)
		{
			if (boxCount > 0)
			{
				boxY = m_vListRect[boxCount - 1].bottom;
			}
			RECT rc = RectMake(boxX, boxY, boxWidth, boxHeight);
			m_vListRect.emplace_back(rc);
			boxCount++;
		}

		m_OKButton.initialize(m_pGraphics, m_pInput,
			unitToolUnitMakeViewerNS::OK_BUTTON_X,
			unitToolUnitMakeViewerNS::OK_BUTTON_Y,
			unitToolUnitMakeViewerNS::OK_BUTTON_FILENAME, true);
		m_OKButton.setRegistFunction(std::bind(&CUnitTool_UnitMakeViewer::functionOKButton));
		m_CancelButton.initialize(m_pGraphics, m_pInput,
			unitToolUnitMakeViewerNS::CANCEL_BUTTON_X,
			unitToolUnitMakeViewerNS::CANCEL_BUTTON_Y,
			unitToolUnitMakeViewerNS::CANCEL_BUTTON_FILENAME, true);
		m_CancelButton.setRegistFunction(std::bind(&CUnitTool_UnitMakeViewer::functionCancelButton));

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, unitToolUnitMakeViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CUnitTool_UnitMakeViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);

	if (m_pInput->getMouseLButton())
	{
		int selectNumber = 0;
		for (auto iter : m_vListRect)
		{
			if (PtInRect(&iter, m_pInput->getMousePt()))
			{
				m_nSelectNumber = selectNumber;
				break;
			}
			selectNumber++;
		}
	}

	m_OKButton.update(frameTime);
	m_CancelButton.update(frameTime);
}

void CUnitTool_UnitMakeViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();
	m_OKButton.render();
	m_CancelButton.render();

	if (m_nSelectNumber != -1)
	{
		m_pGraphics->drawRect(m_vListRect[m_nSelectNumber], 1.0f, graphicsNS::GREEN);
	}
	m_pGraphics->spriteBegin();

	int listCount = 0;
	for (auto iter : m_vShipList)
	{
		m_dxFont.print(iter, m_vListRect[listCount], DT_LEFT | DT_VCENTER);
		listCount++;
	}
	m_pGraphics->spriteEnd();
}

void CUnitTool_UnitMakeViewer::setupShipList(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{
		m_vShipList.emplace_back(iter.substr(iter.rfind('\t') + 1));
	}
}

void CUnitTool_UnitMakeViewer::functionOKButton()
{
	auto selectNum = pThis->m_nSelectNumber;
	if (selectNum < 0)
		return;

	auto shipKey = pThis->m_vShipList[selectNum];
	pThis->m_pUnitToolShipDataSetter->setupShipData(shipKey);
}

void CUnitTool_UnitMakeViewer::functionCancelButton()
{
	pThis->m_nSelectNumber = -1;
}
