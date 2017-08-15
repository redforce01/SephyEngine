#include "stdafx.h"
#include "Battle_ShipUI_Indicator.h"
#include "Battle_Ship.h"

CBattle_ShipUI_Indicator::CBattle_ShipUI_Indicator()
{
	m_pGraphics			= nullptr;
	m_pInput			= nullptr;
	m_strIndicatorKey	= battleShipUIIndicatorNS::INDICATOR_FILENAME + battleShipUIIndicatorNS::INDICATOR_BLUE_KEY + battleShipUIIndicatorNS::INDICATOR_NORMAL_KEY;
	m_enIndicatorType	= INDICATOR_TYPE::INDICATOR_BLUE;
	m_nSpriteNumber		= 0;
	m_rcIndicator		= { 0, };
	m_pMaster			= nullptr;
}


CBattle_ShipUI_Indicator::~CBattle_ShipUI_Indicator()
{
}

bool CBattle_ShipUI_Indicator::initialize(Graphics * g, Input* i, INDICATOR_TYPE type, CBattle_Ship* pMaster)
{
	m_pGraphics = g;
	m_pInput = i;
	m_enIndicatorType = type;
	m_pMaster = pMaster;
	switch (m_enIndicatorType)
	{
	case INDICATOR_TYPE::INDICATOR_BLUE:
		m_strIndicatorTypeKey = battleShipUIIndicatorNS::INDICATOR_BLUE_KEY;
		break;
	case INDICATOR_TYPE::INDICATOR_GREEN:
		m_strIndicatorTypeKey = battleShipUIIndicatorNS::INDICATOR_GREEN_KEY;
		break;
	default:
		m_strIndicatorTypeKey = battleShipUIIndicatorNS::INDICATOR_BLUE_KEY;
		break;
	}
	if (m_nSpriteNumber < 10)
	{
		m_strIndicatorKey += "00" + std::to_string(m_nSpriteNumber);
	}
	else
	{
		m_strIndicatorKey += "0" + std::to_string(m_nSpriteNumber);
	}

	return Image::initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strIndicatorKey));
}

void CBattle_ShipUI_Indicator::update(float frameTime)
{
	updateSprite();
	setUIPos();
}

void CBattle_ShipUI_Indicator::render()
{
	m_pGraphics->spriteBegin();
	Image::draw();
	m_pGraphics->spriteEnd();
}

void CBattle_ShipUI_Indicator::moveX(float distance)
{
	Image::moveX(distance);
}

void CBattle_ShipUI_Indicator::moveY(float distance)
{
	Image::moveY(distance);
}

void CBattle_ShipUI_Indicator::updateSprite()
{
	if (m_nSpriteNumber >= battleShipUIIndicatorNS::INDICATOR_MAX_FRAME)
		m_nSpriteNumber = 0;

	m_rcIndicator = RectMake(Image::spriteData.x, Image::spriteData.y, Image::spriteData.width, Image::spriteData.height);
	if (PtInRect(&m_rcIndicator, m_pInput->getMousePt()))
	{
		m_strIndicatorKey = battleShipUIIndicatorNS::INDICATOR_FILENAME + m_strIndicatorTypeKey + battleShipUIIndicatorNS::INDICATOR_OVERLAB_KEY;
	}
	else
	{
		m_strIndicatorKey = battleShipUIIndicatorNS::INDICATOR_FILENAME + m_strIndicatorTypeKey + battleShipUIIndicatorNS::INDICATOR_NORMAL_KEY;
	}

	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&m_rcIndicator, m_pInput->getMousePt()))
		{
			m_strIndicatorKey = battleShipUIIndicatorNS::INDICATOR_FILENAME + m_strIndicatorTypeKey + battleShipUIIndicatorNS::INDICATOR_CLICK_KEY;
		}
	}

	if (m_nSpriteNumber < 10)
	{
		m_strIndicatorKey += "00" + std::to_string(m_nSpriteNumber);
	}
	else
	{
		m_strIndicatorKey += "0" + std::to_string(m_nSpriteNumber);
	}
	Image::setTextureManager(IMAGEMANAGER->getTexture(m_strIndicatorKey));
	m_nSpriteNumber++;
}

void CBattle_ShipUI_Indicator::setUIPos()
{
	float shipCenterX = m_pMaster->getCurrentCenterX();
	float shipCenterY = m_pMaster->getCurrentCenterY();

	Image::setX(shipCenterX - (Image::getWidth() / 2));
	Image::setY(shipCenterY - (Image::getHeight() / 2) + battleShipUIIndicatorNS::INDICATOR_RELATE_MARGIN);
}
