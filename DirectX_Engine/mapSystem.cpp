#include "stdafx.h"
#include "mapSystem.h"
#include "CameraSystem.h"
#include "mapTileData.h"
#include "logViewer.h"

MapSystem::MapSystem()
{
	m_mapType = MAPTYPE::DIAMOND;
	m_bDebug = true;
	m_pMapTileData = nullptr;
	m_pMapDataParser = nullptr;
	m_pCameraSystem = nullptr;
	m_pLogViewer = nullptr;
}


MapSystem::~MapSystem()
{
	for (auto iter : m_arrTiles)
	{
		SAFE_DELETE(iter);
	}

	SAFE_DELETE(m_pMapDataParser);
}

bool MapSystem::initialize(Game* gamePtr)
{	
	bool success = false;

	m_pMapDataParser = new MapDataParser;
	m_pMapDataParser->setMemoryLinkMapSystem(this);

	int UIDCount = 0;
	int mapX, mapY;
	mapX = mapY = 0;

	if (gamePtr == nullptr)
		return false;

	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();

	for (UINT row = 0; row < MapSystemNS::mapSizeX; row++)
	{
		for (UINT col = 0; col < MapSystemNS::mapSizeY; col++)
		{
			MapTile* temp = new MapTile;
			temp->initialize(gamePtr->getGraphics(), UIDCount, MapSystemNS::BASIC_TILE, mapX, mapY, MapSystemNS::tileBasicWidth, MapSystemNS::tileBasicHeight);
			m_arrTiles.emplace_back(temp);
			
			mapX += MapSystemNS::tileBasicWidth;
			UIDCount++;
		}
		mapY += MapSystemNS::tileBasicHeight / 2;
		
		if (row % 2)
			mapX = 0;
		else mapX = MapSystemNS::tileBasicWidth / 2;
	}
	
	
	return success;
}

void MapSystem::update(float frameTime)
{
	if (m_pInput->getMouseLButton())
	{
		std::string name;
		if (m_pMapTileData == nullptr)
			return;

		for (auto iter : m_arrWorkableRECT)
		{
			if (PtInRect(&iter, m_pInput->getMousePt()))
				return;
		}

		int count = 0;
		name = m_pMapTileData->getTextureName();
		for (auto iter : m_arrTiles)
		{
			if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			{
				count++;
				continue;
			}

			if (MyUtil::getIsometricIn(iter->getTileRect(), m_pInput->getMousePt()))
			{
				if (iter->changeTexture(name))
				{
					std::string log;
					log = "Tile[" + std::to_string(count) + "] Texture Changed : " + name;
					m_pLogViewer->addLog(log);
				}
			}

			count++;
		}
	}

	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			continue;

		iter->update(frameTime);
	}
}

void MapSystem::render()
{
	m_pGraphics->spriteBegin();
	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			continue;
		
		iter->render();
	}
	m_pGraphics->spriteEnd();

	if (m_bDebug)
	{
		for (auto iter : m_arrTiles)
		{
			if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
				continue;

			iter->renderSketch();
		}
	}

}

void MapSystem::moveX(int distance)
{
	for (auto iter : m_arrTiles)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}
}

void MapSystem::moveY(int distance)
{
	for (auto iter : m_arrTiles)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}
}

void MapSystem::scaleUp()
{
	for (auto iter : m_arrTiles)
	{
		iter->increaseScale();
	}
}

void MapSystem::scaleDown()
{
	for (auto iter : m_arrTiles)
	{
		iter->decreaseScale();
	}
}

MapTile * MapSystem::selectTile(int number)
{
	if (m_arrTiles[number] != nullptr)
		return m_arrTiles[number];
	else
		return nullptr;
}

void MapSystem::saveData()
{
	m_pMapDataParser->setMapTiles(m_arrTiles);
	m_pMapDataParser->saveData();
}

void MapSystem::loadData()
{
	m_pMapDataParser->loadData();
}
