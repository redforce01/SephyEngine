#include "stdafx.h"
#include "Battle_ShipHitEvent.h"
#include "Battle_Ship.h"


CBattle_ShipHitEvent::CBattle_ShipHitEvent()
{
	m_pMaster		= nullptr;
	m_pEffectImage	= nullptr;
	m_enEventType	= SHIP_HIT_EVENT_TYPE::SHIP_HIT_EVENT_NULL;
	m_fEventTime	= 0.f;
	m_fCurrentTime	= 0.f;
	m_bActive		= false;
}


CBattle_ShipHitEvent::~CBattle_ShipHitEvent()
{
	SAFE_DELETE(m_pEffectImage);
}

bool CBattle_ShipHitEvent::initialize(CBattle_Ship* pMaster, SHIP_HIT_EVENT_TYPE type)
{
	bool success = false;
	try
	{
		if (pMaster == nullptr)
			return false;

		m_pMaster = pMaster;
		m_enEventType = type;
		m_bActive = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleShipHitEventNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_ShipHitEvent::update(float frameTime)
{
	if (m_bActive == false)
		return;

	m_fCurrentTime += frameTime;
	switch (m_enEventType)
	{
	case SHIP_HIT_EVENT_TYPE::SHIP_HIT_EVENT_CONTROL_TOWER:
		if (m_fCurrentTime > battleShipHitEventNS::CONTROL_TOWER_LOST_TIME)
		{
			m_bActive = false;
			m_pMaster->takeBrokenControlTower(false);
		}
		break;
	case SHIP_HIT_EVENT_TYPE::SHIP_HIT_EVENT_ENGINE_BROKEN:
		if (m_fCurrentTime > battleShipHitEventNS::ENGINE_BROKEN_TIME)
		{
			m_bActive = false;
			m_pMaster->takeEngineBroken(false);
		}
		break;
	case SHIP_HIT_EVENT_TYPE::SHIP_HIT_EVENT_TURRET_BROKEN:
		if (m_fCurrentTime > battleShipHitEventNS::TURRET_BROKEN_TIME)
		{
			m_bActive = false;
			m_pMaster->takeTurretBroken(false);
		}
		break;
	}
}
