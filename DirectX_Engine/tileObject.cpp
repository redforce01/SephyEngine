#include "stdafx.h"
#include "tileObject.h"

TileObject::TileObject()
{
	number = 0;
	type = 0x00000000;
	feature = TILEFEATURE::ISOMETRIC;
}


TileObject::~TileObject()
{
}

bool TileObject::initialize(UINT PID, int startX, int startY,
	Graphics* g, int width, int height, int nCols, TextureManager* texture)
{
	bool success = false;

	number = PID;
	setX(startX);
	setY(startY);
	
	success = Image::initialize(g, width, height, nCols, texture);
	//layer->setLayerState(enLayerList::LAYER_BACKGROUND);	//need to fix, current : Layer = nullptr

	return success;
}

void TileObject::update(float frameTime)
{
	Image::update(frameTime);
}

void TileObject::render()
{
	Image::draw();
}

void TileObject::renderSketch()
{
	if (feature == TILEFEATURE::SQUARE)
	{
		Image::drawRect();
	}
	if (feature == TILEFEATURE::ISOMETRIC)
	{
		Image::drawIsometric();
	}
}
