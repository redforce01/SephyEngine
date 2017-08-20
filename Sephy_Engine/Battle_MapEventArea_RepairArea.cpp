#include "stdafx.h"
#include "Battle_MapEventArea_RepairArea.h"


CBattle_MapEventArea_RepairArea::CBattle_MapEventArea_RepairArea()
{
	m_pGraphics		= nullptr;
	m_pFlag			= nullptr;
	m_AreaCenterX	= 0.f;
	m_AreaCenterY	= 0.f;
	m_AreaRadius	= battleMapEventAreaRepairAreaNS::REPAIR_AREA_RADIUS;
	m_fRepairSpeed	= battleMapEventAreaRepairAreaNS::REPAIR_AREA_REPAIR_SPEED;
	m_AreaCaptureRadius = battleMapEventAreaRepairAreaNS::CAPTURE_RADIUS;
	m_fCaptureTime	= 0.f;
	m_bPlayerArea	= false;
	m_bCapturing	= false;
	//m_bDebug = g_bDebugMode;
	m_bDebug = true;
}


CBattle_MapEventArea_RepairArea::~CBattle_MapEventArea_RepairArea()
{
	SAFE_DELETE(m_pFlag);
	SAFE_DELETE(m_pProgress);
	SAFE_DELETE(m_pProgressback);
}

bool CBattle_MapEventArea_RepairArea::initialize(Graphics* g, float centerX, float centerY)
{
	m_pGraphics = g;
	if (m_pGraphics == nullptr)
		return false;

	bool success = false;
	try
	{
		m_AreaCenterX = centerX;
		m_AreaCenterY = centerY;

		m_pFlag = new Image;
		success = m_pFlag->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleMapEventAreaRepairAreaNS::ENEMY_FLAG));
		m_pFlag->setX(m_AreaCenterX + battleMapEventAreaRepairAreaNS::FLAG_RELATE_X);
		m_pFlag->setY(m_AreaCenterY + battleMapEventAreaRepairAreaNS::FLAG_RELATE_Y);
		m_pProgressback = new Image;
		m_pProgressback->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleMapEventAreaRepairAreaNS::PROGRESS_BACK));
		m_pProgressback->setX(m_AreaCenterX + battleMapEventAreaRepairAreaNS::PROGRESS_RELATE_X);
		m_pProgressback->setY(m_AreaCenterY + battleMapEventAreaRepairAreaNS::PROGRESS_RELATE_Y);
		m_pProgress = new Image;
		m_pProgress->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleMapEventAreaRepairAreaNS::PROGRESS_BLUE));
		m_pProgress->setX(m_AreaCenterX + battleMapEventAreaRepairAreaNS::PROGRESS_RELATE_X + 1);
		m_pProgress->setY(m_AreaCenterY + battleMapEventAreaRepairAreaNS::PROGRESS_RELATE_Y + 1);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapEventAreaRepairAreaNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_MapEventArea_RepairArea::update(float frameTime)
{
	if (m_bPlayerArea)
		return;

	if (m_bCapturing)
	{
		if (m_bCaptureToPlayer)
		{
			m_fCaptureTime += frameTime;
			float rate = (m_fCaptureTime / battleMapEventAreaRepairAreaNS::CAPTURE_TIME) * 100.f;
			auto rc = m_pProgress->getSpriteDataRect();
			rc.right = rc.left + (rate / 100) * battleMapEventAreaRepairAreaNS::PROGRESS_WIDTH;
			m_pProgress->setSpriteDataRect(rc);
			if (m_fCaptureTime >= battleMapEventAreaRepairAreaNS::CAPTURE_TIME)
			{
				m_fCaptureTime = 0.f;
				m_bCapturing = false;
				m_bPlayerArea = true;
				m_pFlag->setTextureManager(IMAGEMANAGER->getTexture(battleMapEventAreaRepairAreaNS::PLAYER_FLAG));
			}
		}
		else
		{
			if (m_fCaptureTime > 0)
			{
				m_fCaptureTime -= frameTime;
				float rate = (m_fCaptureTime / battleMapEventAreaRepairAreaNS::CAPTURE_TIME) * 100.f;
				auto rc = m_pProgress->getSpriteDataRect();
				rc.right = rc.left + (rate / 100) * battleMapEventAreaRepairAreaNS::PROGRESS_WIDTH;
				m_pProgress->setSpriteDataRect(rc);
			}
			else
			{
				m_bCapturing = false;
				m_bPlayerArea = false;
				m_fCaptureTime = 0.f;
				m_pFlag->setTextureManager(IMAGEMANAGER->getTexture(battleMapEventAreaRepairAreaNS::ENEMY_FLAG));
			}
		}
	}
}

void CBattle_MapEventArea_RepairArea::render()
{
	float flagX = m_pFlag->getX();
	float flagY = m_pFlag->getY();
	float flagWidth = m_pFlag->getWidth();
	float flagHeight = m_pFlag->getHeight();

	if (MyUtil::getObjInScreen(flagX, flagY, flagWidth, flagHeight, g_fScreenWidth, g_fScreenHeight))
	{
		m_pGraphics->spriteBegin();
		m_pFlag->draw();

		if (m_fCaptureTime > 0)
		{
			m_pProgressback->draw();
			m_pProgress->draw();
		}
		m_pGraphics->spriteEnd();
	}

	if (m_bDebug)
	{
		if (MyUtil::getObjInScreen(m_AreaCenterX, m_AreaCenterY, m_AreaRadius, m_AreaRadius, g_fScreenWidth, g_fScreenHeight) == false)
			return;

		m_pGraphics->drawCircle(m_AreaCenterX, m_AreaCenterY, m_AreaRadius, 1.0f, graphicsNS::GREEN);
		m_pGraphics->drawCircle(m_AreaCenterX, m_AreaCenterY, m_AreaCaptureRadius, 1.0f, graphicsNS::ORANGE);
	}
}

void CBattle_MapEventArea_RepairArea::moveX(float distance)
{
	m_AreaCenterX += distance;
	m_pFlag->moveX(distance);
	m_pProgressback->moveX(distance);
	m_pProgress->moveX(distance);
}

void CBattle_MapEventArea_RepairArea::moveY(float distance)
{
	m_AreaCenterY += distance;
	m_pFlag->moveY(distance);
	m_pProgressback->moveY(distance);
	m_pProgress->moveY(distance);
}

void CBattle_MapEventArea_RepairArea::capturing(bool bPlayerTo)
{
	m_bCapturing = true;
	m_bCaptureToPlayer = bPlayerTo;
}
