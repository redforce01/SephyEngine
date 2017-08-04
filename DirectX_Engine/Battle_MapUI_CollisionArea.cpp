#include "stdafx.h"
#include "Battle_MapUI_CollisionArea.h"


CBattle_MapUI_CollisionArea::CBattle_MapUI_CollisionArea()
{
	m_rcCollision = { 0, };
	m_x = 0.f; 
	m_y = 0.f;;
	m_width = 0.f;
	m_height = 0.f;
	m_bDebug = true;
}


CBattle_MapUI_CollisionArea::~CBattle_MapUI_CollisionArea()
{
}

bool CBattle_MapUI_CollisionArea::initialize(Game* gamePtr)
{
	bool success = false;
	m_pGraphics = gamePtr->getGraphics();
	success = Entity::initialize(gamePtr, 0, 0, 0, IMAGEMANAGER->getTexture("WHITE"));
	Entity::setCollisionType(battleMapUICollisionAreaNS::DEFAULT_COLLISION_TYPE);
	return success;
}

void CBattle_MapUI_CollisionArea::render()
{
	if (MyUtil::getObjInScreen(m_x, m_y, m_width, m_height, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	if (m_bDebug)
	{
		m_pGraphics->drawRect(m_rcCollision, 1.0f, battleMapUICollisionAreaNS::COLLISION_BOX_COLOR);
	}
}

void CBattle_MapUI_CollisionArea::moveX(float distance)
{
	m_x += distance;
	Image::moveX(distance);
	setupRect();
}

void CBattle_MapUI_CollisionArea::moveY(float distance)
{
	m_y += distance;
	Image::moveY(distance);
	setupRect();
}