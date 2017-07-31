#include "stdafx.h"
#include "Battle_MapUI_StartingArea.h"


CBattle_MapUI_StartingArea::CBattle_MapUI_StartingArea()
{
	m_nSpriteNumber = 0;
	m_nAreaType		= 0;
	m_fAreaRadius	= battleMapUIStartingAreaNS::STARTING_AREA_RADIUS;
	m_centerX = m_centerY = 0.f;
}


CBattle_MapUI_StartingArea::~CBattle_MapUI_StartingArea()
{
	SAFE_DELETE(m_pAreaFlag);
	SAFE_DELETE(m_pAreaFlagShadow);	
}

bool CBattle_MapUI_StartingArea::initialize(Graphics * g, int nAreaType)
{
	bool success = false;

	m_pGraphics = g;
	if (m_pGraphics == nullptr)
		return false;
	try
	{
		m_nAreaType = nAreaType;
		if (m_nAreaType == 0)
		{
			std::string imageKey = battleMapUIStartingAreaNS::STARTING_AREA_FILENAME_KEY;
			std::string typeKey = battleMapUIStartingAreaNS::STARTING_AREA_FLAG_TYPE_A_KEY;
			std::string spriteKey;
			if (m_nSpriteNumber < 10)
				spriteKey = "00";
			else
				spriteKey = "0";
			m_strFlagKey = imageKey + typeKey + spriteKey + std::to_string(m_nSpriteNumber);
			m_strFlagShadowKey = battleMapUIStartingAreaNS::AREA_FLAG_SHADOW_KEY + spriteKey + std::to_string(m_nSpriteNumber);
		}
		else
		{
			std::string imageKey = battleMapUIStartingAreaNS::STARTING_AREA_FILENAME_KEY;
			std::string typeKey = battleMapUIStartingAreaNS::STARTING_AREA_FLAG_TYPE_B_KEY;
			std::string spriteKey;
			if (m_nSpriteNumber < 10)
				spriteKey = "00";
			else
				spriteKey = "0";
			m_strFlagKey = imageKey + typeKey + spriteKey + std::to_string(m_nSpriteNumber);
			m_strFlagShadowKey = battleMapUIStartingAreaNS::AREA_FLAG_SHADOW_KEY + spriteKey + std::to_string(m_nSpriteNumber);
		}

		m_pAreaFlag = new Image;
		success = m_pAreaFlag->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFlagKey));
		m_pAreaFlagShadow = new Image;
		success = m_pAreaFlagShadow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFlagShadowKey));
		m_pAreaFlagShadow->setColorFilter(graphicsNS::UNIT_LIGHT_SHADOW);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapUIStartingAreaNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}


	return false;
}

void CBattle_MapUI_StartingArea::update(float frameTime)
{
	float x = m_pAreaFlag->getX();
	float y = m_pAreaFlag->getY();
	float width = m_pAreaFlag->getWidth();
	float height = m_pAreaFlag->getHeight();
	m_centerX = m_pAreaFlag->getCenterX();
	m_centerY = m_pAreaFlag->getCenterY();

	if (MyUtil::getScreenIn(x, y, width, height, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	if (m_nSpriteNumber >= battleMapUIStartingAreaNS::STARTING_AREA_FLAG_MAX_FRAME)
		m_nSpriteNumber = 0;

	std::string imageKey;
	std::string typeKey;
	std::string spriteKey;
	if (m_nAreaType == 0)
	{
		imageKey = battleMapUIStartingAreaNS::STARTING_AREA_FILENAME_KEY;
		typeKey = battleMapUIStartingAreaNS::STARTING_AREA_FLAG_TYPE_A_KEY;
		if (m_nSpriteNumber < 10)
			spriteKey = "00";
		else
			spriteKey = "0";
		m_strFlagKey = imageKey + typeKey + spriteKey + std::to_string(m_nSpriteNumber);
		m_strFlagShadowKey = battleMapUIStartingAreaNS::AREA_FLAG_SHADOW_KEY + spriteKey + std::to_string(m_nSpriteNumber);
	}
	else
	{
		imageKey = battleMapUIStartingAreaNS::STARTING_AREA_FILENAME_KEY;
		typeKey = battleMapUIStartingAreaNS::STARTING_AREA_FLAG_TYPE_B_KEY;
		if (m_nSpriteNumber < 10)
			spriteKey = "00";
		else
			spriteKey = "0";
		m_strFlagKey = imageKey + typeKey + spriteKey + std::to_string(m_nSpriteNumber);
		m_strFlagShadowKey = battleMapUIStartingAreaNS::AREA_FLAG_SHADOW_KEY + spriteKey + std::to_string(m_nSpriteNumber);
	}
	m_pAreaFlag->setTextureManager(IMAGEMANAGER->getTexture(m_strFlagKey));
	m_pAreaFlagShadow->setTextureManager(IMAGEMANAGER->getTexture(m_strFlagShadowKey));

	m_nSpriteNumber++;

	m_pAreaFlag->update(frameTime);
	m_pAreaFlagShadow->update(frameTime);
}

void CBattle_MapUI_StartingArea::render()
{
	float x = m_pAreaFlag->getX();
	float y = m_pAreaFlag->getY();
	float width = m_pAreaFlag->getWidth();
	float height = m_pAreaFlag->getHeight();

	if (MyUtil::getScreenIn(x, y, width, height, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	m_pGraphics->drawCircle(m_pAreaFlag->getCenterX(), m_pAreaFlag->getCenterY(), m_fAreaRadius, 0.05f, 1.5f, graphicsNS::STARTING_ZONE_LINE);
		
	m_pGraphics->spriteBegin();
	m_pAreaFlag->draw();
	m_pAreaFlagShadow->draw();
	m_pGraphics->spriteEnd();
}

void CBattle_MapUI_StartingArea::moveX(float fDistance)
{
	m_pAreaFlag->moveX(fDistance);
	m_pAreaFlagShadow->moveX(fDistance);
	m_centerX += fDistance;
}

void CBattle_MapUI_StartingArea::moveY(float fDistance)
{
	m_pAreaFlag->moveY(fDistance);
	m_pAreaFlagShadow->moveY(fDistance);
	m_centerY += fDistance;
}

void CBattle_MapUI_StartingArea::setFlagCenterX(float fCenterX)
{
	m_pAreaFlag->setX(fCenterX - m_pAreaFlag->getWidth() / 2);
	m_pAreaFlagShadow->setX(fCenterX - m_pAreaFlag->getWidth() / 2);
	m_centerX = fCenterX;
}

void CBattle_MapUI_StartingArea::setFlagCenterY(float fCenterY)
{
	m_pAreaFlag->setY(fCenterY - m_pAreaFlag->getHeight() / 2);
	m_pAreaFlagShadow->setY(fCenterY - m_pAreaFlag->getHeight() / 2);
	m_centerY = fCenterY;
}
