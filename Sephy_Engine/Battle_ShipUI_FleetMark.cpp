#include "stdafx.h"
#include "Battle_ShipUI_FleetMark.h"
#include "Battle_Ship.h"

CBattle_ShipUI_FleetMark::CBattle_ShipUI_FleetMark()
{
	m_pMaster	= nullptr;
	m_x			= 0;
	m_y			= 0;
	m_width		= battleShipUIFleetMarkNS::FLEET_MARK_WIDTH;
	m_height	= battleShipUIFleetMarkNS::FLEET_MARK_HEIGHT;
	m_strFleetMarkKey = battleShipUIFleetMarkNS::FLEET_MARK_NONE;
}


CBattle_ShipUI_FleetMark::~CBattle_ShipUI_FleetMark()
{
}

bool CBattle_ShipUI_FleetMark::initialize(Graphics * g)
{
	return Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFleetMarkKey));
}

void CBattle_ShipUI_FleetMark::update(float frameTime)
{
	if (m_pMaster == nullptr)
		return;

	setUIPos();
}

void CBattle_ShipUI_FleetMark::draw()
{
	if (m_pMaster == nullptr)
		return;

	Image::draw();
}

void CBattle_ShipUI_FleetMark::moveX(float distance)
{
	Image::moveX(distance);
}

void CBattle_ShipUI_FleetMark::moveY(float distance)
{
	Image::moveY(distance);
}

void CBattle_ShipUI_FleetMark::setUIPos()
{
	auto fShipX = m_pMaster->getCurrentX();
	auto fShipY = m_pMaster->getCurrentY();

	Image::setX(fShipX - battleShipUIFleetMarkNS::FLEET_MARK_POS_X);
	Image::setY(fShipY - battleShipUIFleetMarkNS::FLEET_MARK_POS_Y);
}

void CBattle_ShipUI_FleetMark::setMaster(CBattle_Ship * pShip)
{
	m_pMaster = pShip;
	auto fShipX = m_pMaster->getCurrentX();
	auto fShipY = m_pMaster->getCurrentY();
	Image::setX(fShipX - battleShipUIFleetMarkNS::FLEET_MARK_POS_X);
	Image::setY(fShipY - battleShipUIFleetMarkNS::FLEET_MARK_POS_Y);
}
