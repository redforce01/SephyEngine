#include "stdafx.h"
#include "mapObject.h"


MapObject::MapObject()
{
}


MapObject::~MapObject()
{
}

bool MapObject::initialize(Graphics * g, UINT PID, std::string textureName, int startX, int startY, int width, int height)
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

void MapObject::update(float frameTime)
{
	Image::update(frameTime);
}

void MapObject::render()
{
	Image::draw();
}
