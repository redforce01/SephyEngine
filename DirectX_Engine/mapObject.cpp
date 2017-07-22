#include "stdafx.h"
#include "mapObject.h"


MapObject::MapObject()
{
	m_Number = 0;
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_layer = 0;
	m_rcObject = { 0, };
	m_rcCollisionBox = { 0, };
	m_collisionType = OBJECT_COLLISION_TYPE::COLLISION_BOX;
}


MapObject::~MapObject()
{
}

bool MapObject::initialize(Graphics * g, UINT PID, std::string textureName, OBJECT_COLLISION_TYPE collisionType, UINT layer,
	int startX, int startY, int width, int height)
{
	bool success = false;

	m_Number = PID;
	m_x = startX, m_y = startY;
	m_width = width; m_height = height;
	m_rcObject = RectMake(m_x, m_y, m_width, m_height);
	m_rcCollisionBox = RectMake(m_x, m_y, m_width, m_height);
	m_strTextureName = textureName;
	m_collisionType = collisionType;
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

void MapObject::renderSketch(COLOR_ARGB color)
{
	switch (m_collisionType)
	{
	case OBJECT_COLLISION_TYPE::COLLISION_BOX:
		Image::drawRect(color);
		break;
	case OBJECT_COLLISION_TYPE::COLLISION_CIRCLE:
		Image::drawCircle(color);
		break;
	case OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC:
		Image::drawIsometric(color);
		break;
	}
}
