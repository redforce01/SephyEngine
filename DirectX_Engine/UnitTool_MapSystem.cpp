#include "stdafx.h"
#include "UnitTool_MapSystem.h"


CUnitTool_MapSystem::CUnitTool_MapSystem()
{
}


CUnitTool_MapSystem::~CUnitTool_MapSystem()
{
	for (auto iter : m_vMapCells)
	{
		SAFE_DELETE(m_vMapCells);
	}
	m_vMapCells.clear();

}

bool CUnitTool_MapSystem::initialize(Game* gamePtr)
{
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

	return false;
}

void CUnitTool_MapSystem::update(float frameTime)
{
}

void CUnitTool_MapSystem::render()
{
}
