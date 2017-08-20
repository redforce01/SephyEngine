#ifndef _BATTLE_MAINSYSTEM_H
#define _BATTLE_MAINSYSTEM_H

class CBattle_MainSystem;

#include <string>
#include "systemBase.h"
#include "Battle_DataParser.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"
#include "Battle_UnitSystem.h"
#include "Battle_FleetSystem.h"
#include "Battle_FogSystem.h"
#include "Battle_SoundSystem.h"
#include "Battle_ResultSystem.h"

namespace battleMainSystemNS
{
	const std::string ERROR_MESSAGE = "Main Battle System Initialize Failed";
}

class CBattle_MainSystem : public SystemBase
{
private:
	CBattle_DataParser*		m_pBattle_DataParser;
	CBattle_CameraSystem*	m_pBattle_CameraSystem;
	CBattle_MapSystem*		m_pBattle_MapSystem;
	CBattle_UnitSystem*		m_pBattle_UnitSystem;
	CBattle_FleetSystem*	m_pBattle_FleetSystem;
	CBattle_FogSystem*		m_pBattle_FogSystem;
	CBattle_SoundSystem*	m_pBattle_SoundSystem;
	CBattle_ResultSystem*	m_pBattle_ResultSystem;
public:
	CBattle_MainSystem();
	~CBattle_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	virtual void ai();
	virtual void collision();
};

#endif // !_BATTLE_MAINSYSTEM_H
