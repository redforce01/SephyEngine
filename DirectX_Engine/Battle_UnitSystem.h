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
#include "Battle_UI_FleetListView.h"
#include "Battle_UI_FleetMarkView.h"

namespace battleUnitSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Unit System Initialize Failed";
	const std::string UNIT_BEGIN_KEY = "BEGIN";
	const std::string UNIT_END_KEY = "END";

	const UINT UNIT_NAME_POS = 0;
}

class CBattle_MapSystem;
class CBattle_CameraSystem;
class CBattle_UnitSystem : public SystemBase
{
private: // Forward Declaration
	CBattle_CameraSystem* m_pBattleCameraSystem;
	CBattle_MapSystem* m_pBattleMapSystem;
private:
	typedef std::vector<CBattle_Ship*> arrShips;
	Game* m_pGamePtr;

private: // Unit Variables
	arrShips m_vPlayerShips;	// PLAYER BATTLE SHIPS
	arrShips m_vCompterShips;	// COMPUTER BATTLE SHIPS

	int m_nCurrentBattlePhase;
	int m_nSetupShipIndex;
	int m_nSelectUnitNum;
private:
	bool m_bWorkableSetup;
	bool m_bSelectedUnit;
	bool m_bReSetupShip;
	bool m_bSetupShip;
	bool m_bBattleStart;
private:
	std::vector<RECT> m_vWorkableRect; // UI Workable vector<RECT>

private:
	CBattle_UnitParser*			m_pBattleUnitParser;
	CBattle_UI_Destination*		m_pBattle_UI_Destination;
	CBattle_UI_FleetListView*	m_pBattle_UI_FleetListView;
	CBattle_UI_FleetMarkView*	m_pBattle_UI_FleetMarkView;

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

	//==================================================
	// All Unit Move Functions Called From CameraSystem
	void moveX(float fDistance);
	void moveY(float fDistance);
	//==================================================
	void clearActiveShip();
	void setupShip(std::string shipName);

	void addWorkableRect(RECT rc)
	{
		m_vWorkableRect.emplace_back(rc);
	}
	//==================================================
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
	// Setter Functions
	//==================================================

	void setBattlePhase(int nPhase)
	{
		m_nCurrentBattlePhase = nPhase;
	}

	//==================================================
	// Getter Functions
	//==================================================

	int getBattlePhase() const
	{
		return m_nCurrentBattlePhase;
	}


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
	void setMemoryLinkBattleMapSystem(CBattle_MapSystem* pBattleMapSystem)
	{
		m_pBattleMapSystem = pBattleMapSystem;
	}

};

#endif // !_BATTLE_UNITSYSTEM_H
