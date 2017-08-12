#pragma once
#ifndef _TILEMAP_H
#define _TILEMAP_H

#include "tile.h"
#include "constants.h"
#include <vector>

namespace tileMapNS
{
	const UINT TILEMAP_SIZE_X = 100;
	const UINT TILEMAP_SIZE_Y = 100;
}

class TileMap
{
protected:
	Game* pGame;
	
	Tile arrTile[tileMapNS::TILEMAP_SIZE_X][tileMapNS::TILEMAP_SIZE_Y];
	TextureManager textureTile;

public:
	TileMap();
	~TileMap();

	bool initialize(Game* gamePtr);
	void render();
	void releaseAll();
	void resetAll();
};

#endif // !_TILEMAP_H