#include "stdafx.h"
#include "Battle_MapUI_RespawnArea.h"


CBattle_MapUI_RespawnArea::CBattle_MapUI_RespawnArea()
{
	m_pGraphics = nullptr;
	m_centerX = 0.f;
	m_centerY = 0.f;
	m_areaRadius = 0.f;
}


CBattle_MapUI_RespawnArea::~CBattle_MapUI_RespawnArea()
{
}

bool CBattle_MapUI_RespawnArea::initialize(Graphics * g)
{
	m_pGraphics = g;
	return true;
}

void CBattle_MapUI_RespawnArea::render()
{
	if (MyUtil::getPtInScreen(m_centerX, m_centerY, g_fScreenWidth, g_fScreenHeight))
	{
		m_pGraphics->drawCircle(m_centerX, m_centerY, m_areaRadius, 1.0f, graphicsNS::WHITE);
	}
}
