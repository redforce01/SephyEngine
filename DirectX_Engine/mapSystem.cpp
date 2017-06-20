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
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		SAFE_DELETE(arrTiles[i]);
	}
	arrTiles.clear();
}

bool MapSystem::initialize(Game* gamePtr)
{	
	bool success = false;

	int UIDCount = 0;
	int mapX, mapY;
	mapX = mapY = 0;

	for (UINT row = 0; row < MapSystemNS::mapSizeX; row++)
	{
		for (UINT col = 0; col < MapSystemNS::mapSizeY; col++)
		{
			TileObject* temp = new TileObject;
			temp->initialize(UIDCount, mapX, mapY,
				gamePtr->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("basicTile"));
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
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		if (MyUtil::getScreenIn(arrTiles[i]->getX(), arrTiles[i]->getY(), arrTiles[i]->getWidth(), arrTiles[i]->getHeight(), WINSIZEX, WINSIZEY))
		{
			arrTiles[i]->update(frameTime);
		}
	}
}

void MapSystem::render()
{
	int size = arrTiles.size();
	int maxRenderSizeX = WINSIZEX / MapSystemNS::tileBasicWidth;
	int maxRenderSizeY = WINSIZEY / MapSystemNS::tileBasicHeight;

	for (UINT i = 0; i < size; i++)
	{
		if (MyUtil::getScreenIn(arrTiles[i]->getX(), arrTiles[i]->getY(), arrTiles[i]->getWidth(), arrTiles[i]->getHeight(), WINSIZEX, WINSIZEY))
		{
			arrTiles[i]->render();
			arrTiles[i]->renderSketch();
		}
	}
}

void MapSystem::moveX(float distance)
{
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		arrTiles[i]->moveX(distance);
	}	
}

void MapSystem::moveY(float distance)
{
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		arrTiles[i]->moveY(distance);
	}
}

void MapSystem::scaleUp()
{
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		arrTiles[i]->increaseScale();
	}
}

void MapSystem::scaleDown()
{
	int size = arrTiles.size();
	for (UINT i = 0; i < size; i++)
	{
		arrTiles[i]->decreaseScale();
	}
}

TileObject * MapSystem::selectTile(int number)
{
	if (arrTiles[number] != nullptr)
		return arrTiles[number];
	else
		return nullptr;
}
