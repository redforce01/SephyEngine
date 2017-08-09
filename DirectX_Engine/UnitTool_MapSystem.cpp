#include "stdafx.h"
#include "UnitTool_MapSystem.h"


CUnitTool_MapSystem::CUnitTool_MapSystem()
{
}


CUnitTool_MapSystem::~CUnitTool_MapSystem()
{
	for (auto iter : m_vMapCells)
	{
		SAFE_DELETE(iter);
	}
	m_vMapCells.clear();
}

bool CUnitTool_MapSystem::initialize(Game* gamePtr)
{
	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();

	int UIDCount = 0;
	int mapX, mapY;
	mapX = mapY = 0;
	for (UINT row = 0; row < unitToolMapSystemNS::MAP_CELL_X; row++)
	{
		for (UINT col = 0; col < unitToolMapSystemNS::MAP_CELL_Y; col++)
		{
			MapTile* temp = new MapTile;
			temp->initialize(gamePtr->getGraphics(), 0, unitToolMapSystemNS::BASIC_TILE_C,
				mapX, mapY, unitToolMapSystemNS::MAP_CELL_WIDTH, unitToolMapSystemNS::MAP_CELL_HEIGHT);
			m_vMapCells.emplace_back(temp);

			mapX += unitToolMapSystemNS::MAP_CELL_WIDTH;
			UIDCount++;
		}
		mapY += unitToolMapSystemNS::MAP_CELL_HEIGHT / 2;

		if (row % 2)
			mapX = 0;
		else mapX = unitToolMapSystemNS::MAP_CELL_WIDTH / 2;
	}

	m_fMapCellWidth = unitToolMapSystemNS::MAP_CELL_WIDTH;
	m_fMapCellHeight = unitToolMapSystemNS::MAP_CELL_HEIGHT;
	m_fMapTotalWidth = (unitToolMapSystemNS::MAP_CELL_X * unitToolMapSystemNS::MAP_CELL_WIDTH);
	m_fMapTotalHeight = (unitToolMapSystemNS::MAP_CELL_Y * unitToolMapSystemNS::MAP_CELL_HEIGHT * unitToolMapSystemNS::ISOMETRIC_HEIGHT_TOTAL_RATE + m_fMapCellHeight);

	return true;
}

void CUnitTool_MapSystem::update(float frameTime)
{
	for (auto iter : m_vMapCells)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}
}

void CUnitTool_MapSystem::render()
{
	m_pGraphics->spriteBegin();
	for (auto iter : m_vMapCells)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;
		
		iter->render();
	}
	m_pGraphics->spriteEnd();
}

void CUnitTool_MapSystem::moveX(int distance)
{
	for (auto iter : m_vMapCells)
	{
		iter->moveX(distance);
	}
}

void CUnitTool_MapSystem::moveY(int distance)
{
	for (auto iter : m_vMapCells)
	{
		iter->moveY(distance);
	}
}
