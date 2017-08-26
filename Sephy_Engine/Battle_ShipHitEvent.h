#ifndef _BATTLE_SHIP_HIT_EVENT_H
#define _BATTLE_SHIP_HIT_EVENT_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"

enum class SHIP_HIT_EVENT_TYPE
{
	SHIP_HIT_EVENT_NULL,				// Basic Initialize
	SHIP_HIT_EVENT_CONTROL_TOWER,		// Control Tower Broken - Decrease Rader Max
	SHIP_HIT_EVENT_ENGINE_BROKEN,		// Engine Broken - Decrease Max Speed
	SHIP_HIT_EVENT_TURRET_BROKEN,		// Turret Broken - Decrease Turret Count
	SHIP_HIT_EVENT_SAILOR_DEAD,			// Sailor Dead - Decrease Sailor Count
	SHIP_HIT_EVENT_ARMOR_PENETRATE,		// Armor Penetrate - Hit Critical Damage
	SHIP_HIT_EVENT_HIT_CITADEL,			// Citadel Critical - Hit Critical Damage
};

namespace battleShipHitEventNS
{
	const std::string ERROR_MESSAGE = "Ship Hit Event Initialize Failed";
	const float CONTROL_TOWER_LOST_TIME = 20.f;
	const float ENGINE_BROKEN_TIME = 20.f;
	const float TURRET_BROKEN_TIME = 20.f;
	const std::string CONTROL_TOWER_LOST_IMAGE	= "CategoryShipN";
	const std::string ENGINE_BROKEN_IMAGE		= "CategoryShipN";
	const std::string TURRET_BROKEN_IMAGE		= "ArmGunN";
	const std::string SAILOR_DEAD_IMAGE			= "CategorySailorN";
}

class CBattle_Ship;
class CBattle_ShipHitEvent
{
private:
	CBattle_Ship*		m_pMaster;
	Image*				m_pEffectImage;
	SHIP_HIT_EVENT_TYPE m_enEventType;
	float				m_fEventTime;
	float				m_fCurrentTime;
	bool				m_bActive;
public:
	CBattle_ShipHitEvent();
	~CBattle_ShipHitEvent();

	bool initialize(CBattle_Ship* pMaster, SHIP_HIT_EVENT_TYPE type);
	void update(float frameTime);
	void render();
};

#endif // !_BATTLE_SHIP_HIT_EVENT_H