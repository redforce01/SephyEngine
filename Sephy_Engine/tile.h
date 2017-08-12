#pragma once
#ifndef _TILE_H
#define _TILE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace tileNS
{	
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const enum TILE_TYPE
	{ TILE_TYPE_NONE, TILE_TYPE_GROUMD, TILE_TYPE_WATER, TILE_TYPE_WALL };
	const enum TILE_ANIMATION
	{ TILE_ANIMATION_NONE, TILE_ANIMATION_ANIME };
	const enum TILE_ATTRIBUTE
	{ TILE_ATR_NONE, TILE_ATR_EVENT, TILE_ATR_CHANGE };
	
	const int TILE_EDGE_LEFT = -TILE_WIDTH / 2;
	const int TILE_EDGE_RIGHT = TILE_WIDTH / 2;
	const int TILE_EDGE_TOP = -TILE_HEIGHT / 2;
	const int TILE_EDGE_BOTTOM = TILE_HEIGHT / 2;
	const RECT TILE_EDGE = { TILE_EDGE_LEFT, TILE_EDGE_TOP, TILE_EDGE_RIGHT, TILE_EDGE_BOTTOM };
	const float TILE_MASS = 10000.0f;
}

class Tile
{
protected:
	Entity					tileEntity;

	tileNS::TILE_TYPE		tileType;
	tileNS::TILE_ANIMATION	tileAnimeType;
	tileNS::TILE_ATTRIBUTE	tileAttribute;

public:
	Tile();
	~Tile();

	bool initialize(Game* gamePtr, int width, int height, int nCols, TextureManager* textureM);
	void update(float frameTime);

	void render();
	void releaseAll();
	void resetAll();
};

#endif // _TILE_H
