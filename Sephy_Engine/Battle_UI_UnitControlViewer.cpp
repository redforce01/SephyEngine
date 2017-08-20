#include "stdafx.h"
#include "Battle_UI_UnitControlViewer.h"
#include "Battle_Ship.h"

CBattle_UI_UnitControlViewer* pThis = nullptr;
CBattle_UI_UnitControlViewer::CBattle_UI_UnitControlViewer()
{
	::pThis = this;
	m_pGraphics = nullptr;
	m_pInput = nullptr;
	//==============================================
	m_pBackground	= nullptr;
	m_pShip			= nullptr;
	m_pShipRankMark = nullptr;
	m_bNoneData		= true;
	m_pGunButton	= nullptr;
	m_pAAGunButton	= nullptr;
	m_bAutoGunOnOff		= false;
	m_bAutoAAGunOnOff	= false;
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
	//==============================================
	m_strAutoGunStateMessage = battleUIUnitControlViewerNS::GUN_STATE_OFF;
	m_strAutoAAGunStateMessage = battleUIUnitControlViewerNS::AAGUN_STATE_OFF;
	m_rcAutoGunStateMessage = { 0, };
	m_rcAutoAAGunStateMessage = { 0, };
	//==============================================
	m_pEngineButton = nullptr;
	m_pEngineState	= nullptr;
	m_bFixedEngineOnOff = false;
	m_nEngineBtnSpriteNumber = 3;
	m_strEngineStateMessage = battleUIUnitControlViewerNS::ENGINE_BUTTON_STATE_OFF;
	m_rcEngineStateMessage = { 0, };
}


CBattle_UI_UnitControlViewer::~CBattle_UI_UnitControlViewer()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pGunButton);
	SAFE_DELETE(m_pAAGunButton);
	SAFE_DELETE(m_pEngineButton);
	SAFE_DELETE(m_pEngineState);
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
		
		m_pShipRankMark = new Image;
		m_pShipRankMark->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleUIUnitControlViewerNS::SHIP_RANK_DEFAULT));
		m_pShipRankMark->setX(this->getDialogX() + battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_RANK_MARK_RELATE_X);
		m_pShipRankMark->setY(this->getDialogY() + battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_RANK_MARK_RELATE_Y);

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
		m_rcShipRotateSpeedGuide = RectMake(m_rcShipEngineSpeedGuide.left, m_rcShipEngineSpeedGuide.bottom,
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
		m_rcShipRepairSpeed = RectMake(m_rcShipDP.left, m_rcShipDP.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipEngineSpeed = RectMake(m_rcShipRepairSpeed.left, m_rcShipRepairSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipRotateSpeed = RectMake(m_rcShipEngineSpeed.left, m_rcShipEngineSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		m_rcShipFleetName = RectMake(m_rcShipRotateSpeed.left, m_rcShipRotateSpeed.bottom,
			battleUIUnitControlViewerNS::INFO_VALUE_WIDTH,
			battleUIUnitControlViewerNS::INFO_VALUE_HEIGHT);
		//=========================================================
		m_pGunButton = new SystemButton;
		m_pGunButton->initialize(m_pGraphics, m_pInput,
			this->getDialogX() + battleUIUnitControlViewerNS::GUN_BUTTON_RELATE_X,
			this->getDialogY() + battleUIUnitControlViewerNS::GUN_BUTTON_RELATE_Y,
			battleUIUnitControlViewerNS::GUN_BUTTON_NAME, true);
		m_pGunButton->setRegistFunction(std::bind(&CBattle_UI_UnitControlViewer::functionGunButton));
		m_pAAGunButton = new SystemButton;
		m_pAAGunButton->initialize(m_pGraphics, m_pInput,
			this->getDialogX() + battleUIUnitControlViewerNS::AAGUN_BUTTON_RELATE_X,
			this->getDialogY() + battleUIUnitControlViewerNS::AAGUN_BUTTON_RELATE_Y,
			battleUIUnitControlViewerNS::AAGUN_BUTTON_NAME, true);
		m_pAAGunButton->setRegistFunction(std::bind(&CBattle_UI_UnitControlViewer::functionAAGunButton));
		m_rcAutoGunStateMessage = RectMake(
			this->getDialogX() + battleUIUnitControlViewerNS::GUN_STATE_MESSAGE_RELATE_X, 
			this->getDialogY() + battleUIUnitControlViewerNS::GUN_STATE_MESSAGE_RELATE_Y,
			battleUIUnitControlViewerNS::GUN_STATE_MESSAGE_WIDTH,
			battleUIUnitControlViewerNS::GUN_STATE_MESSAGE_HEIGHT);
		m_rcAutoAAGunStateMessage = RectMake(
			this->getDialogX() + battleUIUnitControlViewerNS::AAGUN_STATE_MESSAGE_RELATE_X,
			this->getDialogY() + battleUIUnitControlViewerNS::AAGUN_STATE_MESSAGE_RELATE_Y,
			battleUIUnitControlViewerNS::AAGUN_STATE_MESSAGE_WIDTH,
			battleUIUnitControlViewerNS::AAGUN_STATE_MESSAGE_HEIGHT);
		//=========================================================
		std::string engineIamgeKey = battleUIUnitControlViewerNS::ENGINE_BUTTON_NAME + std::to_string(m_nEngineBtnSpriteNumber);
		m_pEngineButton = new Image;
		m_pEngineButton->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(engineIamgeKey));
		m_pEngineButton->setX(this->getDialogX() + battleUIUnitControlViewerNS::ENGINE_BUTTON_RELATE_X);
		m_pEngineButton->setY(this->getDialogY() + battleUIUnitControlViewerNS::ENGINE_BUTTON_RELATE_Y);
		m_pEngineState = new Image;
		m_pEngineState->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleUIUnitControlViewerNS::ENGINE_STATE_SIGN_NAME_OFF));
		m_pEngineState->setX(this->getDialogX() + battleUIUnitControlViewerNS::ENGINE_STATE_SIGN_RELATE_X);
		m_pEngineState->setY(this->getDialogY() + battleUIUnitControlViewerNS::ENGINE_STATE_SIGN_RELATE_Y);
		m_rcEngineStateMessage = RectMake(this->getDialogX() + battleUIUnitControlViewerNS::ENGINE_STATE_MESSAGE_RELATE_X,
			this->getDialogY() + battleUIUnitControlViewerNS::ENGINE_STATE_MESSAGE_RELATE_Y,
			battleUIUnitControlViewerNS::ENGINE_STATE_MESSAGE_WIDTH,
			battleUIUnitControlViewerNS::ENGINE_STATE_MESSAGE_HEIGHT);
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

		std::string engineIamgeKey = battleUIUnitControlViewerNS::ENGINE_BUTTON_NAME + std::to_string(m_nEngineBtnSpriteNumber);
		m_pEngineButton->setTextureManager(IMAGEMANAGER->getTexture(engineIamgeKey));
	}
	else
	{
		m_pGunButton->update(frameTime);
		m_pAAGunButton->update(frameTime);

		if (m_bNoneData == true)
		{
			m_strShipName = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipDP = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipEngineSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipRepairSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipRotateSpeed = battleUIUnitControlViewerNS::NONE_DATA;
			m_strShipFleetName = battleUIUnitControlViewerNS::NONE_DATA;

			std::string engineIamgeKey = battleUIUnitControlViewerNS::ENGINE_BUTTON_NAME + std::to_string(m_nEngineBtnSpriteNumber);
			m_pEngineButton->setTextureManager(IMAGEMANAGER->getTexture(engineIamgeKey));
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
			m_strShipRotateSpeed = std::to_string(m_pShip->getRotateSpeed());
			auto strShipRankMark = battleUIUnitControlViewerNS::SHIP_RANK_SMALL_KEY + m_pShip->getShipRankMark();
			m_pShipRankMark->setTextureManager(IMAGEMANAGER->getTexture(strShipRankMark));
			m_bFixedEngineOnOff = m_pShip->getFixedEngineOnOff();
			m_bAutoGunOnOff = m_pShip->getAutoGunOnOff();
			m_bAutoAAGunOnOff = m_pShip->getAutoAAGunOnOff();
			if (m_bAutoGunOnOff)
				m_strAutoGunStateMessage = battleUIUnitControlViewerNS::GUN_STATE_ON;
			else
				m_strAutoGunStateMessage = battleUIUnitControlViewerNS::GUN_STATE_OFF;

			if (m_bAutoAAGunOnOff)
				m_strAutoAAGunStateMessage = battleUIUnitControlViewerNS::AAGUN_STATE_ON;
			else
				m_strAutoAAGunStateMessage = battleUIUnitControlViewerNS::AAGUN_STATE_OFF;

			if (m_pInput->getMouseLButton())
			{
				RECT rc = RectMake(m_pEngineButton->getX(), m_pEngineButton->getY(), m_pEngineButton->getWidth(), m_pEngineButton->getHeight());
				if (PtInRect(&rc, m_pInput->getMousePt()))
				{
					m_bFixedEngineOnOff = !m_bFixedEngineOnOff;
					setupShipEngineOnOff();
					if (m_bFixedEngineOnOff)
					{
						m_strEngineStateMessage = battleUIUnitControlViewerNS::ENGINE_BUTTON_STATE_ON;
						m_pEngineState->setTextureManager(IMAGEMANAGER->getTexture(battleUIUnitControlViewerNS::ENGINE_STATE_SIGN_NAME_ON));
					}
					else
					{
						m_strEngineStateMessage = battleUIUnitControlViewerNS::ENGINE_BUTTON_STATE_OFF;
						m_pEngineState->setTextureManager(IMAGEMANAGER->getTexture(battleUIUnitControlViewerNS::ENGINE_STATE_SIGN_NAME_OFF));
					}
					m_pInput->setMouseLButton(false);
				}				
			}
		}
	}
	
	if (m_bFixedEngineOnOff)
	{
		if (m_nEngineBtnSpriteNumber > 0)
		{
			std::string engineIamgeKey = battleUIUnitControlViewerNS::ENGINE_BUTTON_NAME + std::to_string(m_nEngineBtnSpriteNumber);
			m_pEngineButton->setTextureManager(IMAGEMANAGER->getTexture(engineIamgeKey));
			m_nEngineBtnSpriteNumber--;
		}
	}
	else
	{
		if(m_nEngineBtnSpriteNumber < battleUIUnitControlViewerNS::ENGINE_BUTTON_MAX_FRAME)
		{
			std::string engineIamgeKey = battleUIUnitControlViewerNS::ENGINE_BUTTON_NAME + std::to_string(m_nEngineBtnSpriteNumber);
			m_pEngineButton->setTextureManager(IMAGEMANAGER->getTexture(engineIamgeKey));
			m_nEngineBtnSpriteNumber++;
		}
	}
}

void CBattle_UI_UnitControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGunButton->render();
	m_pAAGunButton->render();

	m_pGraphics->spriteBegin();
	m_pBackground->draw();
	m_pShipRankMark->draw();
	m_pEngineButton->draw();
	m_pEngineState->draw();
	m_dxFont.print(m_strAutoGunStateMessage, m_rcAutoGunStateMessage, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strAutoAAGunStateMessage, m_rcAutoAAGunStateMessage, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strEngineStateMessage, m_rcEngineStateMessage, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_NAME, m_rcShipNameGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_DP, m_rcShipDPGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_REPAIR_SPPED, m_rcShipRepairSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_ENGINE_SPEED, m_rcShipEngineSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_ROTATE_SPEED, m_rcShipRotateSpeedGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(battleUIUnitControlViewerNS::INFO_GUIDE_SHIP_FLEETNAME, m_rcShipFleetNameGuide, DT_LEFT | DT_VCENTER);
	
	m_dxFont.setFontColor(graphicsNS::GREEN);
	m_dxFont.print(m_strShipName, m_rcShipName, DT_LEFT | DT_VCENTER);

	m_dxFont.setFontColor(graphicsNS::WHITE);
	m_dxFont.print(m_strShipDP, m_rcShipDP, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipEngineSpeed, m_rcShipEngineSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipRepairSpeed, m_rcShipRepairSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipRotateSpeed, m_rcShipRotateSpeed, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strShipFleetName, m_rcShipFleetName, DT_LEFT | DT_VCENTER);

	m_pGraphics->spriteEnd();
}

void CBattle_UI_UnitControlViewer::setupShipEngineOnOff()
{
	m_pShip->setFixedEngineOnOff(m_bFixedEngineOnOff);
}

void CBattle_UI_UnitControlViewer::functionGunButton()
{
	pThis->m_bAutoGunOnOff = !pThis->m_bAutoGunOnOff;
	pThis->m_pShip->setAutoGunOnOff(pThis->m_bAutoGunOnOff);
}

void CBattle_UI_UnitControlViewer::functionAAGunButton()
{
	pThis->m_bAutoAAGunOnOff = !pThis->m_bAutoAAGunOnOff;
	pThis->m_pShip->setAutoAAGunOnOff(pThis->m_bAutoAAGunOnOff);
}
