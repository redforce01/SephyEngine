#include "stdafx.h"
#include "Battle_FogSystem.h"
#include "Battle_UnitSystem.h"

CBattle_FogSystem::CBattle_FogSystem()
{
	m_pBattleUnitSystem = nullptr;
}


CBattle_FogSystem::~CBattle_FogSystem()
{
	for (auto iter : m_vFog)
	{
		SAFE_DELETE(iter);
	}
	m_vFog.clear();
}

bool CBattle_FogSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFogSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_FogSystem::update(float frameTime)
{

}

void CBattle_FogSystem::render()
{
	if (m_pBattleUnitSystem->getBattleStart() == false)
		return;

	m_pGraphics->spriteBegin();
	for (auto iter : m_vFog)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->draw();
	}
	m_pGraphics->spriteEnd();
}

void CBattle_FogSystem::moveX(float distance)
{
	for (auto iter : m_vFog)
	{
		iter->moveX(distance);
	}
}

void CBattle_FogSystem::moveY(float distance)
{
	for (auto iter : m_vFog)
	{
		iter->moveY(distance);
	}
}

void CBattle_FogSystem::setupAllFog(float mapTotalWidth, float mapTotalHeight)
{
	float fogWidth = battleFogCellNS::FOG_WIDTH;
	float fogHeight = battleFogCellNS::FOG_HEIGHT;

	int xSize = m_nFogCellX = (mapTotalWidth / fogWidth) + 1;
	int ySize = m_nFogCellY = (mapTotalHeight / fogHeight) + 1;

	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			CBattle_FogCell* fog = new CBattle_FogCell;
			fog->initialize(m_pGraphics, fogWidth * x, fogHeight * y);
			m_vFog.emplace_back(fog);
		}
	}
}
