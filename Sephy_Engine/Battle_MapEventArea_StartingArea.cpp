#include "stdafx.h"
#include "Battle_MapEventArea_StartingArea.h"


CBattle_MapEventArea_StartingArea::CBattle_MapEventArea_StartingArea()
{
	m_nSpriteNumber = 0;
	m_nAreaType		= 0;
	m_fAreaRadius	= battleMapUIStartingAreaNS::STARTING_AREA_RADIUS;
	m_centerX		= 0.f;
	m_centerY		= 0.f;
	//=======================================
	m_pProgressback		= nullptr;
	m_pProgress			= nullptr;
	m_bPlayerArea		= false;
	m_bCapturing		= false;
	m_bCaptureToPlayer	= false;
	m_fCaptureTime		= 0.f;
}


CBattle_MapEventArea_StartingArea::~CBattle_MapEventArea_StartingArea()
{
	SAFE_DELETE(m_pAreaFlag);
	SAFE_DELETE(m_pAreaFlagShadow);	
	SAFE_DELETE(m_pProgressback);
	SAFE_DELETE(m_pProgress);
}

bool CBattle_MapEventArea_StartingArea::initialize(Graphics * g, int nAreaType)
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
		//=========================================================================
		m_pProgressback = new Image;
		m_pProgressback->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleMapUIStartingAreaNS::PROGRESS_BACK));
		m_pProgress = new Image;
		m_pProgress->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleMapUIStartingAreaNS::PROGRESS_BLUE));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapUIStartingAreaNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}


	return false;
}

void CBattle_MapEventArea_StartingArea::update(float frameTime)
{
	float x = m_pAreaFlag->getX();
	float y = m_pAreaFlag->getY();
	float width = m_pAreaFlag->getWidth();
	float height = m_pAreaFlag->getHeight();
	m_centerX = m_pAreaFlag->getCenterX();
	m_centerY = m_pAreaFlag->getCenterY();

	if (m_bCapturing)
	{
		if (m_bCaptureToPlayer)
		{
			m_fCaptureTime += frameTime;
			float rate = (m_fCaptureTime / battleMapUIStartingAreaNS::CAPTURE_TIME) * 100.f;
			auto rc = m_pProgress->getSpriteDataRect();
			rc.right = rc.left + (rate / 100) * battleMapUIStartingAreaNS::PROGRESS_WIDTH;
			m_pProgress->setSpriteDataRect(rc);
			if (m_fCaptureTime >= battleMapUIStartingAreaNS::CAPTURE_TIME)
			{
				m_fCaptureTime = 0.f;
				m_bCapturing = false;
				m_bPlayerArea = true;
			}
		}
		else
		{
			if (m_fCaptureTime > 0)
			{
				m_fCaptureTime -= frameTime;
				float rate = (m_fCaptureTime / battleMapUIStartingAreaNS::CAPTURE_TIME) * 100.f;
				auto rc = m_pProgress->getSpriteDataRect();
				rc.right = rc.left + (rate / 100) * battleMapUIStartingAreaNS::PROGRESS_WIDTH;
				m_pProgress->setSpriteDataRect(rc);
			}
			else
			{
				m_bCapturing = false;
				m_bPlayerArea = false;
				m_fCaptureTime = 0.f;
			}
		}
	}

	if (MyUtil::getObjInScreen(x, y, width, height, g_fScreenWidth, g_fScreenHeight) == false)
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

void CBattle_MapEventArea_StartingArea::render()
{
	float x = m_pAreaFlag->getX();
	float y = m_pAreaFlag->getY();
	float width = m_pAreaFlag->getWidth();
	float height = m_pAreaFlag->getHeight();

	if (MyUtil::getObjInScreen(x, y, width, height, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	m_pGraphics->drawCircle(m_pAreaFlag->getCenterX(), m_pAreaFlag->getCenterY(),
		battleMapUIStartingAreaNS::STARTING_AREA_RADIUS,
		battleMapUIStartingAreaNS::STARTING_AREA_SMOOTHNESS,
		2.0f, graphicsNS::STARTING_ZONE_LINE);
		
	m_pGraphics->spriteBegin();
	m_pAreaFlag->draw();
	m_pAreaFlagShadow->draw();

	if (m_fCaptureTime > 0)
	{
		m_pProgressback->draw();
		m_pProgress->draw();
	}
	m_pGraphics->spriteEnd();
}

void CBattle_MapEventArea_StartingArea::moveX(float fDistance)
{
	m_pAreaFlag->moveX(fDistance);
	m_pAreaFlagShadow->moveX(fDistance);
	m_centerX += fDistance;
	m_pProgressback->moveX(fDistance);
	m_pProgress->moveX(fDistance);
}

void CBattle_MapEventArea_StartingArea::moveY(float fDistance)
{
	m_pAreaFlag->moveY(fDistance);
	m_pAreaFlagShadow->moveY(fDistance);
	m_centerY += fDistance;
	m_pProgressback->moveY(fDistance);
	m_pProgress->moveY(fDistance);
}

void CBattle_MapEventArea_StartingArea::capturing(bool bPlayerTo)
{
	m_bCapturing = true;
	m_bCaptureToPlayer = bPlayerTo;
}

void CBattle_MapEventArea_StartingArea::setFlagCenterX(float fCenterX)
{
	m_pAreaFlag->setX(fCenterX - m_pAreaFlag->getWidth() / 2);
	m_pAreaFlagShadow->setX(fCenterX - m_pAreaFlag->getWidth() / 2);
	m_centerX = fCenterX;
	m_pProgressback->setX(m_centerX + battleMapUIStartingAreaNS::PROGRESS_RELATE_X);
	m_pProgress->setX(m_centerX + battleMapUIStartingAreaNS::PROGRESS_RELATE_X + 1);
}

void CBattle_MapEventArea_StartingArea::setFlagCenterY(float fCenterY)
{
	m_pAreaFlag->setY(fCenterY - m_pAreaFlag->getHeight() / 2);
	m_pAreaFlagShadow->setY(fCenterY - m_pAreaFlag->getHeight() / 2);
	m_centerY = fCenterY;
	m_pProgressback->setY(m_centerY + battleMapUIStartingAreaNS::PROGRESS_RELATE_Y);
	m_pProgress->setY(m_centerY + battleMapUIStartingAreaNS::PROGRESS_RELATE_Y + 1);
}
