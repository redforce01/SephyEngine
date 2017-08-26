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
#include "Battle_UI_FleetMarkViewer.h"
#include "Battle_UI_FleetMakeViewer.h"
#include "Battle_UI_StartButton.h"
#include "Battle_UI_DummyShip.h"
#include "Battle_UI_UnitControlViewer.h"
#include "Battle_UI_PhaseAlert.h"


namespace battleUnitSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Unit System Initialize Failed";
	const std::string UNIT_BEGIN_KEY = "BEGIN";
	const std::string UNIT_END_KEY = "END";
	//==========================================================
	const UINT UNIT_NAME_POS = 0;
	const UCHAR FLEET_SELECT_CONTROL_KEY = VK_CONTROL;
	const UCHAR FLEET_SELECT_SHIFT_KEY = VK_SHIFT;
	const UCHAR MOVETO_OPERATOR_EVENT_POSITION_KEY = VK_SPACE;
	//==========================================================
	const std::string FLEET_MOVE_ORDER_SOUND_NAME = "Voice_OK";
	const std::string SHIP_MOVE_ORDER_SOUND_NAME = "Voice_Confirm";
	const std::string ENEMY_SHIP_INSIGHT_SOUND_NAME = "Voice_Enemyshipinside";
	const std::string BATTLE_START_BGM_PHASE_1_NAME = "battle2";
}

class CBattle_FogSystem;
class CBattle_FleetSystem;
class CBattle_MapSystem;
class CBattle_CameraSystem;
class CBattle_ResultSystem;
class CBattle_UnitSystem : public SystemBase
{
private: // Forward Declaration
	CBattle_CameraSystem*	m_pBattleCameraSystem;
	CBattle_MapSystem*		m_pBattleMapSystem;
	CBattle_FleetSystem*	m_pBattleFleetSystem;
	CBattle_FogSystem*		m_pBattleFogSystem;
	CBattle_ResultSystem*	m_pBattleResultSystem;
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
	bool m_bRePlaceShip;
	bool m_bSetupShip;
	bool m_bBattleStart;
	bool m_bBattleFinish;
	bool m_bPlayerWin;
	bool m_bCreateFleet;
	bool m_bSetUpFlagShip;
private:
	bool m_bClicked;
	bool m_bSimpleClicked;
	bool m_bFleetClicked;
	int m_nClickedFleetNumber;
	float m_fClickStartX;
	float m_fClickStartY;
	float m_fClickEndX;
	float m_fClickEndY;

private:
	std::vector<RECT> m_vWorkableRect; // UI Workable vector<RECT>

private: // Battle Interface 
	CBattle_UnitParser*					m_pBattleUnitParser;
	CBattle_UI_Destination*				m_pBattle_UI_Destination;
	CBattle_UI_FleetListView*			m_pBattle_UI_FleetListView;
	CBattle_UI_FleetMarkViewer*			m_pBattle_UI_FleetMarkView;
	CBattle_UI_FleetMakeViewer*			m_pBattle_UI_FleetMakeView;
	CBattle_UI_StartButton*				m_pBattle_UI_StartButton;
	CBattle_UI_UnitControlViewer*		m_pBattle_UI_ControlView;
	CBattle_UI_PhaseAlert*				m_pBattle_UI_PhaseAlert;
	std::vector<CBattle_UI_DummyShip*>	m_vBattle_UI_DummyShip;

private:
	std::vector<CBattle_Ship*>	m_vFleetMakeShips;
	int							m_nSelectFlagShip;

private: // Variables For Setup Unique ID to Ship
	int m_nLoad_Player_ShipUniqueID;
	int m_nLoad_AI_ShipUniqueID;

private:
	std::string m_strWorldIndex;
public:
	void setWorldIndex(std::string strWorldIndex)
	{
		m_strWorldIndex = strWorldIndex;
	}
	std::string getWorldIndex() const
	{
		return m_strWorldIndex;
	}
private:
	float m_fPlayerDamageScore;
	float m_fComputerDamageScore;
public:
	void addDamageScoreToPlayer(float score)
	{
		m_fPlayerDamageScore += score;
	}
	void addDamageScoreToComputer(float score)
	{
		m_fComputerDamageScore += score;
	}
	float getDamageScoreFromPlayer() const
	{
		return m_fPlayerDamageScore;
	}
	float getDamageScoreFromComputer() const
	{
		return m_fComputerDamageScore;
	}
private: // Bullet
	std::vector<CBattle_Bullet*> m_vBullets;
public:
	void addBulletInBattle(CBattle_Bullet* pBullet)
	{
		m_vBullets.emplace_back(pBullet);
	}

private: // Damage Digits
	std::vector<CBattle_DamageDigit*> m_vDigit;
public:
	void addDamageDigit(CBattle_DamageDigit* pDigit)
	{
		m_vDigit.emplace_back(pDigit);
	}

private: // Operator
	std::vector<CBattle_Operator*> m_vOperator;
public:
	void addOperator(CBattle_Operator* pOperator)
	{
		m_vOperator.emplace_back(pOperator);
	}

private: // Phase System Control
	bool m_bPhaseTwoUp;
	bool m_bPhaseThreeUp;

public:
	CBattle_UnitSystem();
	~CBattle_UnitSystem();

	//==================================================
	// Unit System Initialize
	//  + Each Interface & Unit Setting Initialize
	//  + but UnitSetup Functions Called After Other System Setup
	//==================================================
	virtual bool initialize(Game* gamePtr) override;
	
	//==================================================
	// Unit System Update
	//  + Each Unit Update
	//  + UnitSystem Interface Update
	//  + All Key Input Function Update
	//==================================================
	virtual void update(float frameTime) override;

	//==================================================
	// Unit System Render
	//  + Each Unit Rendering
	//  + UnitSystem Interface Rendering
	//==================================================
	virtual void render() override;

	//==================================================
	// Unit System AI
	//  + Each Unit AI Update
	//==================================================
	virtual void ai();

	//==================================================
	// UnitSystem Collision
	//  + Each Unit Collision Update
	//  + All EnemyShip Detection Update
	//==================================================
	virtual void collision();

	//==================================================
	// All Player Ship Load & Enemy Ship Load
	//  + Load Ship Data from Battle_Data File
	//==================================================
	void loadPlayerShipData(std::vector<std::string> vArray);
	void loadAIShipData(std::vector<std::string> vArray);

private:
	std::vector<std::string> functionTokenize(std::string strData);


public: 
	//==================================================
	// Member Functions
	//==================================================
	void updateFuncBeforeStart(float frameTime);
	void updateFuncAfterStart(float frameTime);

	void setupEnemyShips();
	//==================================================
	// All Unit Move Functions Called From CameraSystem
	void moveX(float fDistance);
	void moveY(float fDistance);
	//==================================================
	void clearActiveShip();
	void setupShip(std::string shipName);
	void setupActiveForStart();

	void setupFleetToFleetSystem();

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

public:
	//==================================================
	// Sound Functions
	//==================================================
	void playSoundEnemyShipInSight();


	//==================================================
	// Setter Functions
	//==================================================

	void setBattlePhase(int nPhase)
	{
		m_nCurrentBattlePhase = nPhase;
	}

	void setBattleStart(bool bStart)
	{
		m_pBattle_UI_FleetMakeView->setActive(false);
		m_bBattleStart = bStart;
		setupEnemyShips();
	}

	void setBattleFinish(bool bFinish)
	{
		m_bBattleFinish = bFinish;
	}

	void setCreateFleet(bool bCreateFleet)
	{
		m_bCreateFleet = bCreateFleet;
	}

	void setSetupFlagShip(bool bSetUpFlagShip)
	{
		m_bSetUpFlagShip = bSetUpFlagShip;
	}

	//==================================================
	// Getter Functions
	//==================================================

	int getBattlePhase() const
	{
		return m_nCurrentBattlePhase;
	}

	bool getBattleStart() const
	{
		return m_bBattleStart;
	}

	bool getBattleFinish() const
	{
		return m_bBattleFinish;
	}

	std::vector<CBattle_Ship*> getPlayerShips() const
	{
		return m_vPlayerShips;
	}
	std::vector<CBattle_Ship*> getComputerShips() const
	{
		return m_vCompterShips;
	}

	bool getCreateFleet() const
	{
		return m_bCreateFleet;
	}

	bool getSetupFlagShip() const
	{
		return m_bSetUpFlagShip;
	}

	std::vector<CBattle_Ship*> getFleetMakeShips() const
	{
		return m_vFleetMakeShips;
	}

	bool getPlayerWin() const
	{
		return m_bPlayerWin;
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
	void setMemoryLinkBattleFleetSystem(CBattle_FleetSystem* pBattleFleetSystem)
	{
		m_pBattleFleetSystem = pBattleFleetSystem;
	}
	void setMemoryLinkBattleFogSystem(CBattle_FogSystem* pBattleFogSystem)
	{
		m_pBattleFogSystem = pBattleFogSystem;
	}
	void setMemoryLinkBattleResultSystem(CBattle_ResultSystem* pBattleResultSystem)
	{
		m_pBattleResultSystem = pBattleResultSystem;
	}
};

#endif // !_BATTLE_UNITSYSTEM_H
