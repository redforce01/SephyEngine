#include "stdafx.h"
#include "Battle_FogSystem.h"
#include "Battle_UnitSystem.h"
#include "Battle_MapSystem.h"

CBattle_FogSystem::CBattle_FogSystem()
{
	m_pBattleMapSystem = nullptr;
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

		int fogWidthSize = (g_fScreenWidth / battleFogSystemNS::FOG_WIDTH) + 1;
		int fogHeightSize = (g_fScreenHeight / battleFogSystemNS::FOG_HEIGHT) + 1;

		for (int y = 0; y < fogHeightSize; y++)
		{
			for (int x = 0; x < fogWidthSize; x++)
			{
				CBattle_FogCell* pNewFog = new CBattle_FogCell;
				pNewFog->initialize(m_pGraphics,
					battleFogSystemNS::FOG_WIDTH * x,
					battleFogSystemNS::FOG_HEIGHT * y);
				m_vFog.emplace_back(pNewFog);
			}
		}
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFogSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_FogSystem::update(float frameTime)
{
	for (auto fogIter : m_vFog)
	{
		RECT rcFog = RectMake(fogIter->getX(), fogIter->getY(), fogIter->getWidth(), fogIter->getHeight());
		
		bool checkSuccess = false;
		auto vPlayerShips = m_pBattleUnitSystem->getPlayerShips();
		for (auto shipIter : vPlayerShips)
		{
			if (shipIter->getShipActive() == false)
				continue;

			if (shipIter->getShipDestroy())
				continue;
			
			float shipCenterX = shipIter->getCurrentCenterX();
			float shipCenterY = shipIter->getCurrentCenterY();
			float raderRange = shipIter->getRaderRange();

			if (MyUtil::circleInRect(shipCenterX, shipCenterY, raderRange, &rcFog) == false)
				continue;

			checkSuccess = true;
		}
		
		auto vObserverArea = m_pBattleMapSystem->getObserverArea();
		for (auto obsIter : vObserverArea)
		{
			if (obsIter->isPlayerArea() == false)
				continue;

			float obsCenterX = obsIter->getAreaCenterX();
			float obsCenterY = obsIter->getAreaCenterY();
			float obsRadius = obsIter->getAreaSightRadius();

			if (MyUtil::circleInRect(obsCenterX, obsCenterY, obsRadius, &rcFog) == false)
				continue;

			checkSuccess = true;
		}

		if (checkSuccess)
		{
			fogIter->setTextureManager(IMAGEMANAGER->getTexture(battleFogCellNS::FOG_NONE_CELL_FILENAME));
		}
		else
		{
			fogIter->setTextureManager(IMAGEMANAGER->getTexture(battleFogCellNS::FOG_FULL_CELL_FILENAME));
		}
	}
}

void CBattle_FogSystem::render()
{
	if (m_pBattleUnitSystem->getBattleStart() == false)
		return;

	m_pGraphics->spriteBegin();

	for (auto iter : m_vFog)
	{
		iter->draw();
		//iter->drawRect();
	}

	m_pGraphics->spriteEnd();
}