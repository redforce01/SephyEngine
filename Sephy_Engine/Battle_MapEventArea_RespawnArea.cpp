#include "stdafx.h"
#include "Battle_MapEventArea_RespawnArea.h"


CBattle_MapEventArea_RespawnArea::CBattle_MapEventArea_RespawnArea()
{
	m_pGraphics = nullptr;
	m_centerX = 0.f;
	m_centerY = 0.f;
	m_areaRadius = 0.f;
}


CBattle_MapEventArea_RespawnArea::~CBattle_MapEventArea_RespawnArea()
{
}

bool CBattle_MapEventArea_RespawnArea::initialize(Graphics * g)
{
	m_pGraphics = g;
	return true;
}

void CBattle_MapEventArea_RespawnArea::render()
{
	if (MyUtil::getObjInScreen(m_centerX, m_centerY, m_areaRadius, m_areaRadius, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	m_pGraphics->drawCircle(m_centerX, m_centerY, m_areaRadius, 1.0f, graphicsNS::WHITE);
}
