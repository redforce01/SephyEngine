#include "stdafx.h"
#include "mapSystem.h"
#include "CameraSystem.h"
#include "mapTileData.h"

MapSystem::MapSystem()
{
	m_mapType = MAPTYPE::DIAMOND;
	m_pCameraSystem = nullptr;
	m_pMapTileData = nullptr;
}


MapSystem::~MapSystem()
{
	for (auto iter : m_arrTiles)
	{
		SAFE_DELETE(iter);
	}
}

bool MapSystem::initialize(Game* gamePtr)
{	
	bool success = false;

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
			TileObject* temp = new TileObject;
			temp->initialize(UIDCount, mapX, mapY,
				gamePtr->getGraphics(), MapSystemNS::tileBasicWidth, MapSystemNS::tileBasicHeight, 0, IMAGEMANAGER->getTexture("isoBasicC"));
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

		name = m_pMapTileData->getTileName();
		for (auto iter : m_arrTiles)
		{
			if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
				continue;

			if (MyUtil::getIsometricIn(iter->getTileRect(), m_pInput->getMousePt()))
			{
				iter->setTextureManager(IMAGEMANAGER->getTexture(name));
			}
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

	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			continue;

		iter->renderSketch();
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

TileObject * MapSystem::selectTile(int number)
{
	if (m_arrTiles[number] != nullptr)
		return m_arrTiles[number];
	else
		return nullptr;
}
