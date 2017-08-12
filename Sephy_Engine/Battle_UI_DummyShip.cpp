#include "stdafx.h"
#include "Battle_UI_DummyShip.h"


CBattle_UI_DummyShip::CBattle_UI_DummyShip()
{
	m_fDeltaTime	= 0.f;
	m_fSetupTime	= battleUIDummyShipNS::DEFAULT_SETUP_TIME;
	m_bSetup		= false;
	m_nShipIndex	= -1;
}


CBattle_UI_DummyShip::~CBattle_UI_DummyShip()
{
}

bool CBattle_UI_DummyShip::initialize(Game * gamePtr, std::string shipName, int shipIndex, float setupTime)
{
	bool success = false;
	m_nShipIndex = shipIndex;
	m_fSetupTime = setupTime;
	success = CBattle_Ship::initialize(gamePtr, shipName);
	CBattle_Ship::setDummyShip(true);
	CBattle_Ship::setShipColorFilter(battleUIDummyShipNS::DUMMY_FILTER);
	return success;
}

void CBattle_UI_DummyShip::update(float frameTime)
{
	if (m_bSetup)
		return;

	m_fDeltaTime += frameTime;
	if (m_fDeltaTime > m_fSetupTime)
		m_bSetup = true;

	CBattle_Ship::update(frameTime);
}

void CBattle_UI_DummyShip::render()
{
	if (m_bSetup)
		return;

	CBattle_Ship::render();
}