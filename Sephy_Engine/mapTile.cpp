#include "stdafx.h"
#include "mapTile.h"

MapTile::MapTile()
{
	m_Number = 0;
	m_nType = 0x00000000;
	m_Feature = TILEFEATURE::FEATULRE_ISOMETRIC;
	m_rcTile = { 0, };
}


MapTile::~MapTile()
{
}

bool MapTile::initialize(Graphics* g, UINT PID, std::string textureName, int startX, int startY,
	int width, int height)
{
	bool success = false;

	m_Number = PID;
	m_rcTile = RectMake(startX, startY, width, height);
	m_strTextureName = textureName;
	setX(startX);
	setY(startY);
	
	success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strTextureName));
	//layer->setLayerState(enLayerList::LAYER_BACKGROUND);	//need to fix, current : Layer = nullptr

	return success;
}

void MapTile::update(float frameTime)
{
	Image::update(frameTime);
}

void MapTile::render()
{
	Image::draw();
}

void MapTile::renderSketch(COLOR_ARGB color)
{
	if (m_Feature == TILEFEATURE::FEATULRE_SQUARE || m_Feature == TILEFEATURE::FEATULRE_UNKNOWN)
	{
		Image::drawRect(color);
	}
	else if (m_Feature == TILEFEATURE::FEATULRE_ISOMETRIC)
	{
		Image::drawIsometric(color);
	}
	else if (m_Feature == TILEFEATURE::FEATULRE_CIRCLE)
	{
		Image::drawCircle(color);
	}
}
