#ifndef _BATTLE_UNITSYSTEM_H
#define _BATTLE_UNITSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UnitSystem;

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "systemBase.h"
#include "Battle_UnitParser.h"
#include "Battle_Ship.h"
#include "Battle_UI_Destination.h"
#include "Battle_UI_FleetCategory.h"

namespace battleUnitSystemNS
{
	const std::string UNIT_BEGIN_KEY = "BEGIN";
	const std::string UNIT_END_KEY = "END";

	const UINT UNIT_NAME_POS = 0;
}


class CBattle_CameraSystem;
class CBattle_UnitSystem : public SystemBase
{
private: // Forward Declaration
	CBattle_CameraSystem* m_pBattleCameraSystem;

private:
	typedef std::vector<CBattle_Ship*> arrShips;
	Game* m_pGamePtr;

private: // Unit Variables
	arrShips m_vPlayerShips;	// PLAYER BATTLE SHIPS
	arrShips m_vCompterShips;	// COMPUTER BATTLE SHIPS

private:
	CBattle_UnitParser*			m_pBattleUnitParser;
	CBattle_UI_Destination*		m_pBattle_UI_Destination;
	CBattle_UI_FleetCategory*	m_pBattle_UI_FleetCategory;
private:
	bool m_bSelectedUnit;

public:
	CBattle_UnitSystem();
	~CBattle_UnitSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	virtual void ai();
	virtual void collision();

	void loadPlayerShipData(std::vector<std::string> vArray);
	void loadAIShipData(std::vector<std::string> vArray);

private:
	std::vector<std::string> functionTokenize(std::string strData);


public: 
	//==================================================
	// Member Functions
	//==================================================

	void moveX(float fDistance);
	void moveY(float fDistance);

	// Add Player Ship Function
	void addPlayerShip(CBattle_Ship* pNewShip)
	{
		m_vPlayerShips.emplace_back(pNewShip);
	}
	// Add Computer Ship Function
	void addComputerShip(CBattle_Ship* pNewShip)
	{
		m_vCompterShips.emplace_back(pNewShip);
	}

	//==================================================
	// Getter Functions
	//==================================================

	std::vector<CBattle_Ship*> getPlayerShips() const
	{
		return m_vPlayerShips;
	}
	std::vector<CBattle_Ship*> getComputerShips() const
	{
		return m_vCompterShips;
	}

	//==================================================
	// Forward Declaration MemoryLink Functions
	//==================================================
	void setMemoryLinkBattleCameraSystem(CBattle_CameraSystem* pBattleCameraSystem)
	{
		m_pBattleCameraSystem = pBattleCameraSystem;
	}

};

#endif // !_BATTLE_UNITSYSTEM_H
