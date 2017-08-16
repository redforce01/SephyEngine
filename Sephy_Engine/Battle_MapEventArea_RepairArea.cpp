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
	m_fCaptureRate	= 0.f;
	m_bPlayerArea	= false;
	m_bCapturing	= false;
	//m_bDebug = g_bDebugMode;
	m_bDebug = true;
}


CBattle_MapEventArea_RepairArea::~CBattle_MapEventArea_RepairArea()
{
	SAFE_DELETE(m_pFlag);
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
		if (success == false)
			throw("Error");
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapEventAreaRepairAreaNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_MapEventArea_RepairArea::update(float frameTime)
{
	if (m_bCapturing)
	{
		if (m_bPlayerArea == m_bCaptureToPlayer)
		{
			m_bCapturing = false;
			return;
		}

		m_fCaptureRate += battleMapEventAreaRepairAreaNS::REPAIR_AREA_CAPTURE_SPEED  * frameTime;
		if (m_fCaptureRate >= battleMapEventAreaRepairAreaNS::CAPTURE_TIME)
		{
			if (m_bCaptureToPlayer)
			{
				m_fCaptureRate = 0.f;
				m_bCapturing = false;
				m_bPlayerArea = true;
			}
			else
			{
				m_fCaptureRate = 0.f;
				m_bCapturing = false;
				m_bPlayerArea = false;
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
		m_pGraphics->spriteEnd();
	}
	
	if (MyUtil::getObjInScreen(m_AreaCenterX, m_AreaCenterY, m_AreaRadius, m_AreaRadius, g_fScreenWidth, g_fScreenHeight) == false)
		return;
	
	m_pGraphics->drawCircle(m_AreaCenterX, m_AreaCenterY, m_AreaRadius, 1.0f, graphicsNS::GREEN);
}

void CBattle_MapEventArea_RepairArea::moveX(float distance)
{
	m_AreaCenterX += distance;
	m_pFlag->moveX(distance);
}

void CBattle_MapEventArea_RepairArea::moveY(float distance)
{
	m_AreaCenterY += distance;
	m_pFlag->moveY(distance);
}

void CBattle_MapEventArea_RepairArea::capturing(bool bPlayerTo)
{
	m_bCapturing = true;
	m_bCaptureToPlayer = bPlayerTo;
}
