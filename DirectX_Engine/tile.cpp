#include "stdafx.h"
#include "tile.h"


Tile::Tile()
{
	tileType = tileNS::TILE_TYPE_NONE;	
	tileAnimeType = tileNS::TILE_ANIMATION_NONE;
	tileAttribute = tileNS::TILE_ATR_NONE;

}


Tile::~Tile()
{
}

bool Tile::initialize(Game * gamePtr, int width, int height, int nCols, TextureManager * textureM)
{
	if (false == tileEntity.initialize(gamePtr, width, height, nCols, textureM))
		return false;
	
	tileEntity.setEdge(tileNS::TILE_EDGE);
	tileEntity.setCollisionType(entityNS::BOX);
	tileEntity.setMass(tileNS::TILE_MASS);
	tileEntity.setNoBounce(true);


	return true;
}

void Tile::update(float frameTime)
{
	
}

void Tile::render()
{		
	tileEntity.draw();
}

void Tile::releaseAll()
{	
}

void Tile::resetAll()
{
}
