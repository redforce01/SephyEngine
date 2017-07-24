#ifndef _BATTLE_MAINSYSTEM_H
#define _BATTLE_MAINSYSTEM_H

class CBattle_MainSystem;

#include <string>
#include "systemBase.h"
#include "Battle_DataParser.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"

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

public:
	CBattle_MainSystem();
	~CBattle_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_BATTLE_MAINSYSTEM_H
