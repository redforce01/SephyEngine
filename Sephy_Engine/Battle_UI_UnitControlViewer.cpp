#include "stdafx.h"
#include "Battle_UI_UnitControlViewer.h"
#include "Battle_Ship.h"

CBattle_UI_UnitControlViewer::CBattle_UI_UnitControlViewer()
{
	m_pBackground	= nullptr;
	m_pShip			= nullptr;
	m_bNoneData		= true;
	//==============================================
	m_rcShipNameGuide			= { 0, };
	m_rcShipDPGuide				= { 0, };
	m_rcShipEngineSpeedGuide	= { 0, };
	m_rcShipRepairSpeedGuide	= { 0, };
	m_rcShipRotateSpeedGuide	= { 0, };
	m_rcShipFleetNameGuide		= { 0, };
	m_strShipName				= battleUIUnitControlViewerNS::NONE_DATA;
	m_strShipDP					= battleUIUnitControlViewerNS::NONE_DATA;
	m_strShipEngineSpeed		= battleUIUnitControlViewerNS::NONE_DATA;
	m_strShipRepairSpeed		= battleUIUnitControlViewerNS::NONE_DATA;
	m_strShipRotateSpeed		= battleUIUnitControlViewerNS::NONE_DATA;
	m_strShipFleetName			= battleUIUnitControlViewerNS::NONE_DATA;
	//==============================================
	m_rcShipNameGuide = { 0, };
	m_rcShipDPGuide = { 0, };
	m_rcShipEngineSpeedGuide = { 0, };
	m_rcShipRepairSpeedGuide = { 0, };
	m_rcShipRotateSpeedGuide = { 0, };
	m_rcShipFleetNameGuide = { 0, };
	//==============================================
	fontColor = battleUIUnitControlViewerNS::FONT_COLOR;
	backColor = battleUIUnitControlViewerNS::BACK_COLOR;
	
}


CBattle_UI_UnitControlViewer::~CBattle_UI_UnitControlViewer()
{
	SAFE_DELETE(m_pBackground);
}

bool CBattle_UI_UnitControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth + battleUIUnitControlViewerNS::CONTROL_VIEWER_RELATE_X,
			g_fScreenHeight + battleUIUnitControlViewerNS::CONTROL_VIEWER_RELATE_Y,
			battleUIUnitControlViewerNS::CONTROL_VIEWER_WIDTH,
			battleUIUnitControlViewerNS::CONTROL_VIEWER_HEIGHT, 0);
		
		m_pBackground = new Image;
		success = m_pBackground->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleUIUnitControlViewerNS::CONTROL_VIEWER_BACKGROUND));
		m_pBackground->setX(SystemUIDialog::getDialogX());
		m_pBackground->setY(SystemUIDialog::getDialogY());
		
		success = m_dxFont.initialize(m_pGraphics, battleUIUnitControlViewerNS::FONT_HEIGHT, false, false, battleUIUnitControlViewerNS::FONT);
		//=========================================================
		m_rcShipNameGuide = RectMake(this->getDialogX() + battleUIUnitControlViewerNS::INFO_GUIDE_START_X,
			this->getDialogY() + battleUIUnitControlViewerNS::INFO_GUIDE_START_Y,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		m_rcShipDPGuide = RectMake(m_rcShipNameGuide.left, m_rcShipNameGuide.bottom,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		m_rcShipRepairSpeedGuide = RectMake(m_rcShipDPGuide.left, m_rcShipDPGuide.bottom,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		m_rcShipEngineSpeedGuide = RectMake(m_rcShipRepairSpeedGuide.left, m_rcShipRepairSpeedGuide.bottom,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		m_rcShipRotateSpeedGuide = RectMake(m_rcShipRepairSpeedGuide.left, m_rcShipRepairSpeedGuide.bottom,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		m_rcShipFleetNameGuide = RectMake(m_rcShipRotateSpeedGuide.left, m_rcShipRotateSpeedGuide.bottom,
			battleUIUnitControlViewerNS::INFO_GUIDE_WIDTH,
			battleUIUnitControlViewerNS::INFO_GUIDE_HEIGHT);
		//=========================================================
		m_rcShipName = RectMake(this->getDialogX() + battleUIUnitControlViewerNS::INFO_VALUE_START_X,
			this->getDialogY() + battleUIUnitControlViewerNS::INFO_VALUE_START_Y,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipDP = RectMake(m_rcShipName.left, m_rcShipName.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipEngineSpeed = RectMake(m_rcShipDP.left, m_rcShipDP.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipRepairSpeed = RectMake(m_rcShipEngineSpeed.left, m_rcShipEngineSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipRotateSpeed = RectMake(m_rcShipRepairSpeed.left, m_rcShipRepairSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipFleetName = RectMake(m_rcShipRotateSpeed.left, m_rcShipRotateSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		//=========================================================


	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIUnitControlViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_UnitControlViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);

	if (m_pShip == nullptr)
	{
		m_strShipName = battleUIUnitControlViewerNS::NONE_DATA;
		m_strShipDP = battleUIUnitControlViewerNS::NONE_DATA;
		m_strShipEngineSpeed = battleUIUnitControlViewerNS::NONE_DATA;
		m_strShipRepairSpeed = battleUIUnitControlViewerNS::NONE_DATA;
		m_strShipRotateSpeed = battleUIUnitControlViewerNS::NONE_DATA;
		m_strShipFleetName = battleUIUnitControlViewerNS::NONE_DATA;
	}
	else
	{
		if (m_bNoneData == true)
		{
			m_strShipName = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipDP = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipEngineSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipRepairSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipRotateSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipFleetName = battleUIUnitControlViewerNS::NONE_DATA;
		}
		else
		{
			m_strShipName = m_pShip->getShipName();
			auto strCurDP = std::to_string((int)m_pShip->getCurrentHealth());
			auto strMaxDP = std::to_string((int)m_pShip->getMaxHealth());
			m_strShipDP = strCurDP + "/" + strMaxDP;
			m_strShipRepairSpeed = std::to_string((int)m_pShip->getRepairSpeed());
			auto strCurSpeed = std::to_string((int)m_pShip->getCurrentSpeed());
			auto strMaxSpeed = std::to_string((int)m_pShip->getMaxSpeed());
			m_strShipEngineSpeed = strCurSpeed + "/" + strMaxSpeed;
			m_strShipRotateSpeed = std::to_string((int)m_pShip->getRotateSpeed());
		}
	}
}

void CBattle_UI_UnitControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();
	m_pBackground->draw();
	
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_NAME, m_rcShipNameGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_DP, m_rcShipDPGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_REPAIR_SPPED, m_rcShipRepairSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_ENGINE_SPEED, m_rcShipEngineSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_ROTATE_SPEED, m_rcShipRotateSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_FLEETNAME, m_rcShipFleetNameGuide, DT_LEFT | DT_VCENTER);
	
	m_dxFont.setFontColor(graphicsNS::RED);
	m_dxFont.print(m_strShipName, m_rcShipName, DT_LEFT | DT_VCENTER);

	m_dxFont.setFontColor(graphicsNS::WHITE);
	m_dxFont.print(m_strShipDP, m_rcShipDP, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipEngineSpeed, m_rcShipEngineSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipRepairSpeed, m_rcShipRepairSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipRotateSpeed, m_rcShipRotateSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipFleetName, m_rcShipFleetName, DT_LEFT | DT_VCENTER);

	m_pGraphics->spriteEnd();
}
