#include "stdafx.h"
#include "mapSystem.h"
#include "CameraSystem.h"

MapSystem::MapSystem()
{
	mapType = MAPTYPE::SQUARE;
	pCameraSystem = nullptr;
}


MapSystem::~MapSystem()
{
	for (auto iter : arrTiles)
	{
		if(iter != nullptr)
			SAFE_DELETE(iter);
		iter = nullptr;
	}
	arrTiles.clear();
}

bool MapSystem::initialize(Game* gamePtr)
{	
	bool success = false;

	int UIDCount = 0;
	int mapX, mapY;
	mapX = mapY = 0;

	if (gamePtr == nullptr)
		return false;

	pGraphics = gamePtr->getGraphics();
	pInput = gamePtr->getInput();

	for (UINT row = 0; row < MapSystemNS::mapSizeX; row++)
	{
		for (UINT col = 0; col < MapSystemNS::mapSizeY; col++)
		{
			TileObject* temp = new TileObject;
			temp->initialize(UIDCount, mapX, mapY,
				gamePtr->getGraphics(), MapSystemNS::tileBasicWidth, MapSystemNS::tileBasicHeight, 0, IMAGEMANAGER->getTexture("isoBasicA"));
			arrTiles.emplace_back(temp);
			
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
	for (auto iter : arrTiles)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			continue;

		iter->update(frameTime);
	}
}

void MapSystem::render()
{
	pGraphics->spriteBegin();

	for (auto iter : arrTiles)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), WINSIZEX, WINSIZEY) == false)
			continue;

		iter->renderSketch();			
		iter->render();
	}

	pGraphics->spriteEnd();
}

void MapSystem::moveX(int distance)
{
	for (auto iter : arrTiles)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}
}

void MapSystem::moveY(int distance)
{
	for (auto iter : arrTiles)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}
}

void MapSystem::scaleUp()
{
	for (auto iter : arrTiles)
	{
		iter->increaseScale();
	}
}

void MapSystem::scaleDown()
{
	for (auto iter : arrTiles)
	{
		iter->decreaseScale();
	}
}

TileObject * MapSystem::selectTile(int number)
{
	if (arrTiles[number] != nullptr)
		return arrTiles[number];
	else
		return nullptr;
}
