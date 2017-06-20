#include "stdafx.h"
#include "tileMap.h"


TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

bool TileMap::initialize(Game * gamePtr)
{
	pGame = gamePtr;

	for(UINT i=0; i < tileMapNS::TILEMAP_SIZE_X; i++)
	{
		for (UINT j = 0; j < tileMapNS::TILEMAP_SIZE_Y; j++)
		{
			arrTile[i][j].initialize(pGame, tileNS::TILE_WIDTH, tileNS::TILE_HEIGHT, 10, );
		}
	}

	return false;
}

void TileMap::render()
{
	for (UINT i = 0; i < tileMapNS::TILEMAP_SIZE_X; i++)
	{
		for (UINT j = 0; j < tileMapNS::TILEMAP_SIZE_Y; j++)
		{
			
		}
	}
	
}

void TileMap::releaseAll()
{
}

void TileMap::resetAll()
{
}
