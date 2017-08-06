#include "stdafx.h"
#include "Battle_ShipUI_State.h"
#include "Battle_Ship.h"

CBattle_ShipUI_State::CBattle_ShipUI_State()
{
	m_pMaster			= nullptr;
	m_pGraphics			= nullptr;
	//================================================
	m_pDPBack			= nullptr;
	m_pDPProgress		= nullptr;
	m_pShipGuide		= nullptr;
	m_pShipRank			= nullptr;
	m_strDPProgressKey	= battleShipUIStateNS::DP_GUAGE_GREEN_FILENAME;
	m_strShipRankKey = battleShipUIStateNS::SHIP_RANK_CHIEF;
	//================================================
	m_maxDP				= 0.f; 
	m_currentDP			= 0.f;
	m_maxWidth			= battleShipUIStateNS::DP_MAX_PROGRESS_WIDTH;
	m_targetWidth		= 0.f;
	m_bAnimation		= false;
}


CBattle_ShipUI_State::~CBattle_ShipUI_State()
{
	SAFE_DELETE(m_pDPBack);
	SAFE_DELETE(m_pDPProgress);
	SAFE_DELETE(m_pShipGuide);
	SAFE_DELETE(m_pShipRank);
}

bool CBattle_ShipUI_State::initialize(Graphics * g, CBattle_Ship * pMaster)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pMaster = pMaster;

		m_strShipName	= m_pMaster->getShipName();
		m_currentDP		= m_pMaster->getCurrentHealth();
		m_maxDP			= m_pMaster->getMaxHealth();		


		success = m_dxFont.initialize(m_pGraphics, battleShipUIStateNS::FONT_HEIGHT, battleShipUIStateNS::FONT_BOLD, false, battleShipUIStateNS::FONT);
		//=================================================
		// ShipUI State Image Initialize
		//  + DP Background
		//  + DP Progress
		//  + Ship GuideLine
		//  + Ship Rank Mark
		//=================================================
		m_pShipGuide = new Image;
		m_pShipGuide->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleShipUIStateNS::SHIP_GUIDE_FILENAME));
		m_pShipGuide->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_GUIDE_RELATE_X);
		m_pShipGuide->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_GUIDE_RELATE_Y);


		m_pShipRank = new Image;
		m_pShipRank->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strShipRankKey));
		m_pShipRank->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_SHIPRANK_RELATE_X);
		m_pShipRank->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_SHIPRANK_RELATE_Y);


		m_pDPBack = new Image;
		m_pDPBack->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleShipUIStateNS::DP_BACKPANNEL_FILENAME));
		m_pDPBack->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_DP_BACK_RELATE_X);
		m_pDPBack->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_DP_BACK_RELATE_Y);

		m_pDPProgress = new Image;
		m_pDPProgress->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strDPProgressKey));
		m_pDPProgress->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_PROGRESS_RELATE_X);
		m_pDPProgress->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_PROGRESS_RELATE_Y);
		
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleShipUIStateNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_ShipUI_State::update(float frameTime)
{
	auto currentRate = (m_currentDP / m_maxDP) * 100;
	
	if (currentRate >= battleShipUIStateNS::DP_COLOR_RATE_GREEN)
	{
		m_strDPProgressKey = battleShipUIStateNS::DP_GUAGE_GREEN_FILENAME;
	}
	else if (currentRate >= battleShipUIStateNS::DP_COLOR_RATE_YELLOW)
	{
		m_strDPProgressKey = battleShipUIStateNS::DP_GUAGE_YELLOW_FILENAME;
	}
	else if (currentRate >= battleShipUIStateNS::DP_COLOR_RATE_ORANGE)
	{
		m_strDPProgressKey = battleShipUIStateNS::DP_GUAGE_ORANGE_FILENAME;
	}
	else
	{
		m_strDPProgressKey = battleShipUIStateNS::DP_GUAGE_RED_FILENAME;
	}
	m_pDPProgress->setTextureManager(IMAGEMANAGER->getTexture(m_strDPProgressKey));

	setupStateUIPos();
}

void CBattle_ShipUI_State::render()
{
	m_pGraphics->spriteBegin();

	RECT rc;
	rc = RectMake(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_SHIPNAME_RELATE_X,
		m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_SHIPNAME_RELATE_Y,
		battleShipUIStateNS::STATE_UI_SHIPNAME_BOX_WIDTH,
		battleShipUIStateNS::STATE_UI_SHIPNAME_BOX_HEIGHT);
	m_dxFont.print(m_strShipName, rc, DT_LEFT | DT_VCENTER);
	m_pShipGuide->draw();
	m_pShipRank->draw();
	m_pDPBack->draw();
	m_pDPProgress->draw();
	m_pGraphics->spriteEnd();
}

void CBattle_ShipUI_State::moveX(float distance)
{
	m_pDPBack->moveX(distance);
	m_pDPProgress->moveX(distance);
	m_pShipGuide->moveX(distance);
	m_pShipRank->moveX(distance);
}

void CBattle_ShipUI_State::moveY(float distance)
{
	m_pDPBack->moveY(distance);
	m_pDPProgress->moveY(distance);
	m_pShipGuide->moveY(distance);
	m_pShipRank->moveY(distance);
}

void CBattle_ShipUI_State::setupStateUIPos()
{
	m_pShipGuide->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_GUIDE_RELATE_X);
	m_pShipGuide->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_GUIDE_RELATE_Y);
	m_pShipRank->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_SHIPRANK_RELATE_X);
	m_pShipRank->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_SHIPRANK_RELATE_Y);
	m_pDPBack->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_DP_BACK_RELATE_X);
	m_pDPBack->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_DP_BACK_RELATE_Y);
	m_pDPProgress->setX(m_pMaster->getCurrentCenterX() + battleShipUIStateNS::STATE_UI_PROGRESS_RELATE_X);
	m_pDPProgress->setY(m_pMaster->getCurrentCenterY() + battleShipUIStateNS::STATE_UI_PROGRESS_RELATE_Y);
}

void CBattle_ShipUI_State::damageToDP(float damage)
{
	//m_bAnimation = true;
	//auto dpRate = (m_currentDP / m_maxDP) * 100;
	//auto widthRate = m_maxWidth / 100 * dpRate;
	//m_targetWidth = widthRate;
}

void CBattle_ShipUI_State::updateAnimation()
{

}
