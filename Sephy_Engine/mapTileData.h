#ifndef _MAPTILEDATA_H
#define _MAPTILEDATA_H

class MapTileData;

#include <string>
#include "image.h"
#include "mapObject.h"

namespace mapTileDataNS
{
	const UINT TILE_WIDTH = 128;
	const UINT TILE_HEIGHT = 64;
}

class MapTileData : public Image
{
private:
	Graphics*	m_pGraphics;
	std::string m_textureName;
	float		m_x, m_y;
	float		m_width, m_height;
	int			m_layer;
	bool		m_bObjectable;
	bool		m_bFreePosition;
	bool		m_bSelected;
	RECT		m_rcImage;
	OBJECT_COLLISION_TYPE m_collisionType;
public:
	MapTileData();
	~MapTileData();

	bool initialize(Graphics* g, std::string name, float startX, float startY);
	void draw();

	void reset();
	// ===========================================
	// Setter Functions 
	// ===========================================
	void setObjectable(bool b)
	{
		m_bObjectable = b;
	}
	void setLayer(int layer)
	{
		m_layer = layer;
	}
	void setPosition(int x, int y)
	{
		m_x = x, m_y = y;
		this->setX(m_x);
		this->setY(m_y);
	}
	void setWidth(int width)
	{
		m_width = width;
	}
	void setHeight(int height)
	{
		m_height = height;
	}
	void setTextureName(std::string name)
	{
		m_textureName = name;
	}
	void setFreePosition(bool b)
	{
		m_bFreePosition = b;
	}
	void setSelected(bool b)
	{
		m_bSelected = b;
	}
	void setCollisionType(OBJECT_COLLISION_TYPE type)
	{
		m_collisionType = type;
	}
	// ===========================================
	// Getter Functions 
	// ===========================================
	std::string getTextureName() const
	{
		return m_textureName;
	}
	bool getObjectable() const
	{
		return m_bObjectable;
	}
	int getLayer() const
	{
		return m_layer;
	}
	POINT getPosition() const
	{
		return PointMake(m_x, m_y);
	}
	int getWidth() const
	{
		return m_width;
	}
	int getHeight() const
	{
		return m_height;
	}
	bool getFreePosition() const
	{
		return m_bFreePosition;
	}
	bool getSelected() const
	{
		return m_bSelected;
	}
	RECT getTileDataRECT() const
	{
		return m_rcImage;
	}
	OBJECT_COLLISION_TYPE getCollisionType() const
	{
		return m_collisionType;
	}
};

#endif // !_MAPTILEDATA_H
