#ifndef _BATTLE_MAP_EVENT_AREA_COLLISIONAREA_H
#define _BATTLE_MAP_EVENT_AREA_COLLISIONAREA_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_CollisionArea;

#include "entity.h"

namespace battleMapUICollisionAreaNS
{
	const entityNS::COLLISION_TYPE DEFAULT_COLLISION_TYPE = entityNS::COLLISION_TYPE::PIXEL_PERFECT;
	const COLOR_ARGB COLLISION_BOX_COLOR = SETCOLOR_ARGB(255, 128, 128, 192);
}

class CBattle_MapEventArea_CollisionArea : public Entity
{
private:
	Graphics* m_pGraphics;

private:
	RECT	m_rcCollision;
	float	m_x, m_y;
	float	m_width, m_height;
	bool	m_bDebug;
public:
	CBattle_MapEventArea_CollisionArea();
	~CBattle_MapEventArea_CollisionArea();

	bool initialize(Game* gamePtr);
	void render();

	//========================================
	// Member Functions
	//========================================

	void moveX(float distance);
	void moveY(float distance);


	void setupRect()
	{ m_rcCollision = RectMake(m_x, m_y, m_width, m_height); }

	//========================================
	// Setter Functions
	//========================================

	void setCollisionX(float x)
	{
		m_x = x;
		Entity::setX(x);
		setupRect();
	}

	void setCollisionY(float y)
	{
		m_y = y;
		Entity::setY(y);
		setupRect();
	}

	void setCollisionWidth(float width)
	{
		m_width = width;
		Entity::setWidth(width);
		setupRect();
	}

	void setCollisionHeight(float height)
	{
		m_height = height;
		Entity::setHeight(height);
		setupRect();
	}

	//========================================
	// Getter Functions
	//========================================

	float getCollisionX() const
	{
		return m_x;
	}
	float getCollisionY() const
	{
		return m_y;
	}
	float getCollisionCenterX() const
	{
		return m_x + (m_width / 2);
	}
	float getCollisionCenterY() const
	{
		return m_y + (m_height / 2);
	}
	float getCollisionWidth() const
	{
		return m_width;
	}
	float getCollisionHeight() const
	{
		return m_height;
	}
};

#endif // !_BATTLE_MAP_EVENT_AREA_COLLISIONAREA_H
