#include "stdafx.h"
#include "Battle_UI_FleetMakeViewer.h"
#include "Battle_UnitSystem.h"

CBattle_UI_FleetMakeViewer* pThis = nullptr;
CBattle_UI_FleetMakeViewer::CBattle_UI_FleetMakeViewer()
{
	::pThis = this;
	backColor = battleUIFleetMakeViewerNS::BACK_COLOR_ACTIVE;
	m_bVisibleView			= false;
	m_pBattleUnitSystem		= nullptr;
	//==================================================
	m_rcFlagShipTypeGuide = { 0, };
	m_rcFlagShipNameGuide = { 0, };
	m_rcFlagShipTypeMessage = { 0, };
	m_rcFlagShipNameMessage = { 0, };
	m_strFlagShipTypeGuide = battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_TYPE_GUIDE;
	m_strFlagShipNameGuide = battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_NAME_GUIDE;
	m_strFlagShipType = battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_MESSAGE_NA;
	m_strFlagShipName = battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_MESSAGE_NA;
	//==================================================
	m_bFleetMakeMode		= false;
	m_bActive				= true;
	m_strFleetMakeSignKey	= battleUIFleetMakeViewerNS::FLEET_MAKE_OFF_SIGN_KEY;
}


CBattle_UI_FleetMakeViewer::~CBattle_UI_FleetMakeViewer()
{
	SAFE_DELETE(m_pFleetMakeButton);
	SAFE_DELETE(m_pFleetRemoveButton);
	SAFE_DELETE(m_pFleetSetupButton);
	SAFE_DELETE(m_pFlagShipButton);
}

bool CBattle_UI_FleetMakeViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = m_dxFont.initialize(g, battleUIFleetMakeViewerNS::FONT_HEIGHT, false, false, battleUIFleetMakeViewerNS::FONT);
		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_WIDTH - battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_MARGIN,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_Y,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_WIDTH,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_HEIGHT, 0);
		//=================================================================================
		m_pFleetMakeButton = new CBattle_UI_FleetMakeButton;
		m_pFleetMakeButton->initialize(g, i);
		m_pFleetMakeButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetMake));		
		m_pFleetRemoveButton = new CBattle_UI_FleetRemoveButton;
		m_pFleetRemoveButton->initialize(g, i);
		m_pFleetRemoveButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetRemove));
		m_pFleetSetupButton = new CBattle_UI_FleetSetupButton;
		m_pFleetSetupButton->initialize(g, i);
		m_pFleetSetupButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetSetup));
		m_pFlagShipButton = new CBattle_UI_FlagShipButton;
		m_pFlagShipButton->initialize(g, i);
		m_pFlagShipButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionSetFlagShip));
		//=================================================================================
		float viewX = g_fScreenWidth - battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_WIDTH + battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_MARGIN;
		float viewY = battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_Y;
		float guideStartHeight = 60.f;
		m_rcFlagShipTypeGuide = RectMake(viewX, viewY + guideStartHeight, battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_WIDTH, battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_HEIGHT);
		m_rcFlagShipNameGuide = RectMake(m_rcFlagShipTypeGuide.left, m_rcFlagShipTypeGuide.bottom,
			battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_WIDTH, 
			battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_HEIGHT);
		float guideWidth = (m_rcFlagShipTypeGuide.right - m_rcFlagShipTypeGuide.left);
		float messageWidth = g_fScreenWidth - (viewX + guideWidth) - (battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_MARGIN * 2);
		m_rcFlagShipTypeMessage = RectMake(m_rcFlagShipTypeGuide.right + 10, m_rcFlagShipTypeGuide.top,
			messageWidth,
			battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_HEIGHT);
		m_rcFlagShipNameMessage = RectMake(m_rcFlagShipTypeMessage.left, m_rcFlagShipNameGuide.top,
			messageWidth,
			battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_HEIGHT);
		//=================================================================================
		m_pFleetMakeSign = new Image;
		m_pFleetMakeSign->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFleetMakeSignKey));
		auto signPosX = m_pFlagShipButton->getButtonX() - 10;
		auto signPosY = m_pFlagShipButton->getButtonCenterY() - (m_pFleetMakeSign->getHeight() / 2);
		m_pFleetMakeSign->setX(signPosX);
		m_pFleetMakeSign->setY(signPosY);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIFleetMakeViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetMakeViewer::update(float frameTime)
{
	if (SystemUIDialog::getVisible() == false)
		return;

	SystemUIDialog::update(frameTime);

	if (m_bActive == false)
	{
		if (this->getDialogX() < g_fScreenWidth)
		{
			float speed = battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_SPEED * frameTime;
			moveDialogX(speed);
			m_pFleetMakeButton->moveX(speed);
			m_pFleetRemoveButton->moveX(speed);
			m_pFleetSetupButton->moveX(speed);
			m_pFlagShipButton->moveX(speed);
			m_pFleetMakeSign->moveX(speed);
			m_rcFlagShipTypeGuide.left += speed;
			m_rcFlagShipTypeGuide.right += speed;
			m_rcFlagShipNameGuide.left += speed;
			m_rcFlagShipNameGuide.right += speed;
			m_rcFlagShipTypeMessage.left += speed;
			m_rcFlagShipTypeMessage.right += speed;
			m_rcFlagShipNameMessage.left += speed;
			m_rcFlagShipNameMessage.right += speed;
		}

		return;
	}
	
	if (m_bFleetMakeMode)
	{
		m_strFleetMakeSignKey = battleUIFleetMakeViewerNS::FLEET_MAKE_ON_SIGN_KEY;
		m_pFleetMakeSign->setTextureManager(IMAGEMANAGER->getTexture(m_strFleetMakeSignKey));
	}
	else
	{
		m_strFleetMakeSignKey = battleUIFleetMakeViewerNS::FLEET_MAKE_OFF_SIGN_KEY;
		m_pFleetMakeSign->setTextureManager(IMAGEMANAGER->getTexture(m_strFleetMakeSignKey));
	}

	if (SystemUIDialog::getMouseOver() == false)
		return;

	m_pFleetMakeButton->update(frameTime);
	m_pFleetRemoveButton->update(frameTime);
	m_pFleetSetupButton->update(frameTime);
	m_pFlagShipButton->update(frameTime);
}

void CBattle_UI_FleetMakeViewer::render()
{
	if (SystemUIDialog::getVisible() == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->drawRect(m_rcFlagShipTypeGuide);
	m_pGraphics->drawRect(m_rcFlagShipNameGuide);
	m_pGraphics->drawRect(m_rcFlagShipTypeMessage);
	m_pGraphics->drawRect(m_rcFlagShipNameMessage);
	m_pGraphics->drawLine(m_rcFlagShipNameGuide.left,
		m_rcFlagShipNameGuide.bottom + battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_BOX_BOTTOM_MARGIN,
		m_rcFlagShipNameGuide.left + battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_BOX_BOTTOM_LINE_WIDTH,
		m_rcFlagShipNameGuide.bottom + battleUIFleetMakeViewerNS::FLEET_FLAG_SHIP_GUIDE_BOX_BOTTOM_MARGIN);

	m_pGraphics->spriteBegin();
	m_pFleetMakeSign->draw();
	m_dxFont.print(m_strFlagShipNameGuide, m_rcFlagShipNameGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strFlagShipTypeGuide, m_rcFlagShipTypeGuide, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strFlagShipName, m_rcFlagShipNameMessage, DT_LEFT | DT_VCENTER);
	m_dxFont.print(m_strFlagShipType, m_rcFlagShipTypeMessage, DT_LEFT | DT_VCENTER);
	m_pGraphics->spriteEnd();

	m_pFleetMakeButton->render();
	m_pFleetRemoveButton->render();
	m_pFleetSetupButton->render();
	m_pFlagShipButton->render();
}

void CBattle_UI_FleetMakeViewer::functionFleetMake()
{
	pThis->m_bVisibleView = !pThis->m_bVisibleView;
}

void CBattle_UI_FleetMakeViewer::functionFleetRemove()
{

}

void CBattle_UI_FleetMakeViewer::functionFleetSetup()
{
	pThis->m_bFleetMakeMode = false;
	pThis->m_pBattleUnitSystem->setupFleetToFleetSystem();
}

void CBattle_UI_FleetMakeViewer::functionSetFlagShip()
{
	bool bTodo = false;
	auto ships = pThis->m_pBattleUnitSystem->getPlayerShips();
	for (auto iter : ships)
	{
		if (iter->getShipActive() == false)
			continue;

		bTodo = true;
		break;
	}
	
	if (bTodo)
	{
		pThis->m_bFleetMakeMode = true;
		pThis->m_pBattleUnitSystem->setSetupFlagShip(true);
	}
}
