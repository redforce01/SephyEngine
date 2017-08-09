#ifndef _UNITTOOL_UIVIEWER_H
#define _UNITTOOL_UIVIEWER_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_UIViewer;

#include "systemUIDialog.h"
#include "systemButton.h"
#include "Battle_Ship.h"
#include "systemUIEdit.h"

namespace unitToolUIViewerNS
{
	const std::string ERROR_MESSAGE = "Unit Tool UnitInformation Viewer Initialize Failed";
	const float VIEWER_RELATE_X = 10;
	const float VIEWER_RELATE_Y = 10;
	const float VIEWER_RELATE_WIDTH = 380;
	const float VIEWER_RELATE_HEIGHT = 580;
	//================================================================
	const char	FONT[] = "Courier New";
	const int	FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
	//================================================================
	const UINT ITEM_BOX_START_MARGIN = 10;
	const UINT ITEM_SIZE = 28;
	const UINT ITEM_GUIDE_BOX_WIDTH = 150;
	const UINT ITEM_GUIDE_BOX_HEIGHT = 18;
	const UINT ITEM_BOX_WIDTH = 150;
	const UINT ITEM_BOX_HEIGHT = 18;
	//================================================================
	const std::string UP_BUTTON_FILENAME		= "Up";
	const std::string DOWN_BUTTON_FILENAME		= "Down";
	const std::string OK_BUTTON_FILENAME		= "OK";
	const std::string CANCEL_BUTTON_FILENAME	= "Cancel";
	const UINT UP_BUTTON_MARGIN_BETWEEN_ITEM = 5;
	const UINT DOWN_BUTTON_MARGIN_BETWEEN_ITEM = 20;
	//================================================================
	const std::string SETUP_BUTTON_FILENAME = "Setup";
	const std::string REMOVE_BUTTON_FILENAME = "Remove";
	const UINT SETUP_BUTTON_RELATE_X = 20;
	const UINT SETUP_BUTTON_RELATE_Y = 12;
	const UINT REMOVE_BUTTON_RELATE_X = 80;
	const UINT REMOVE_BUTTON_RELATE_Y = 12;
	const std::string SETUP_PLAYER_BUTTON_FILENAME = "Set";
	const std::string SETUP_PLAYER_STATUS_ON_FILENAME = "onSign";
	const std::string SETUP_PLAYER_STATUS_OFF_FILENAME = "offSign";
	const UINT SETUP_PLAYER_STATUS_RELATE_X = 160;
	const UINT SETUP_PLAYER_STATUS_RELATE_Y = 15;
	const UINT SETUP_PLAYER_BUTTON_RELATE_X = 175;
	const UINT SETUP_PLAYER_BUTTON_RELATE_Y = 3;
	//================================================================
	const std::string ITEM_NONE_ARGUMENT			= "N/A";
	const std::string INFO_TITLE_ID					= "ID";
	const std::string INFO_TITLE_TEXTURE_KEY		= "Texture Key";
	const std::string INFO_TITLE_TOP_COUNT			= "Top Count";
	const std::string INFO_TITLE_BODY_COUNT			= "Body Count";
	const std::string INFO_TITLE_BOTTOM_COUNT		= "Bottom Count";
	const std::string INFO_TITLE_NAME				= "Name";
	const std::string INFO_TITLE_TYPE_A				= "Ship Type";
	const std::string INFO_TITLE_TYPE_B				= "Unit Type";
	const std::string INFO_TITLE_MAX_DP				= "Max DP";
	const std::string INFO_TITLE_CURRENT_DP			= "Current DP";
	const std::string INFO_TITLE_REPAIR_SPEED		= "Repair Speed";
	const std::string INFO_TITLE_ROTATE_SPEED		= "Rotate Speed";
	const std::string INFO_TITLE_ACCELERATE_SPEED	= "Accelerate Speed";
	const std::string INFO_TITLE_MAX_SPEED			= "Max Speed";
	const std::string INFO_TITLE_CURRENT_SPEED		= "Current Speed";
	const std::string INFO_TITLE_RADER_RANGE		= "Rader Range";
	const std::string INFO_TITLE_TURRET_CAPACITY	= "Turret Capacity";
	const std::string INFO_TITLE_TURRET_NAME		= "Turret Name";
	const std::string INFO_TITLE_AIRCRAFT_CAPACITY	= "AirCraft Capacity";
	const std::string INFO_TITLE_PERFORMANCE		= "Performance";
	const std::string INFO_TITLE_SAILOR				= "Sailor";
	const std::string INFO_TITLE_ANTIAIR_CAPACITY	= "Antiair Capacity";
	const std::string INFO_TITLE_ANTIAIR_RANGE		= "Antiair Range";
	const std::string INFO_TITLE_ANTIAIR_DAMAGE		= "Antiair Damage";
	const std::string INFO_TITLE_PHASE				= "Phase";
	const std::string INFO_TITLE_MASS				= "Mass";
	const std::string INFO_TITLE_EVASION			= "Evasion Radius";
	const std::string INFO_TITLE_SKILL				= "Skill";
	//================================================================
}

struct tagUpDownPair
{
	SystemButton buttonUp;
	SystemButton buttonDown;
};

class CUnitTool_MouseOverShip;
class CUnitTool_UIViewer : public SystemUIDialog
{
	CUnitTool_MouseOverShip* m_pMouseOverShip;
public:
	void setMemoryLinkMouseOverShip(CUnitTool_MouseOverShip* pMouseOverShip)
	{
		m_pMouseOverShip = pMouseOverShip;
	}
private:
	Game* m_pGame;
public:
	void setupGamePointer(Game* pGame)
	{
		m_pGame = pGame;
	}
private:
	std::vector<tagUpDownPair*> m_vUpDownPairButton;
	std::string		m_strPlayerStatusKey;
	bool m_bSetupShip;
	bool m_bPlayerShip;
private:
	SystemButton	m_SetupButton;
	SystemButton	m_RemoveButton;

	SystemButton	m_SetPlayerShipButton;
	Image			m_SetPlayerStatus;
private:
	bool	m_bFocusItemBox;
	int		m_nFocusItemNumber;
private:
	std::vector<SystemUIEdit*> m_vEditControl;

private:
	std::string m_ID;					// 01. Ship ID
	std::string m_TextureKey;			// 02. TextureKey
	std::string m_TopCount;				// 03. TopCount
	std::string m_BodyCount;			// 04. BodyCount
	std::string m_BottomCount;			// 05. BottomCount
	std::string m_Name;					// 06. ShipName
	std::string m_ShipType;				// 07. ShipType
	std::string m_UnitType;				// 08. UnitType
	std::string m_MaxDP;				// 09. MaxDP
	std::string m_CurrentDP;			// 10. CurrentDP
	std::string m_RepairSpeed;			// 11. RepairSpeed
	std::string m_RotateSpeed;			// 12. RotateSpeed
	std::string m_AccelerateSpeed;		// 13. AccelerateSpeed
	std::string m_MaxSpeed;				// 14. MaxSpeed
	std::string m_CurrentSpeed;			// 15. CurrentSpeed
	std::string m_RaderRange;			// 16. RaderRange
	std::string m_TurretCapacity;		// 17. Turret Capacity
	std::string m_TurretName;			// 18. Turret Name
	std::string m_AircraftCapacity;		// 19. Aircraft Capacity
	std::string m_Performance;			// 20. Performance
	std::string m_Sailor;				// 21. Sailor
	std::string m_AntiAirCapacity;		// 22. Antiair Capacity
	std::string m_AntiAirRange;			// 23. Antiair Range
	std::string m_AntiAirDamage;		// 24. Antiair Damage
	std::string m_Phase;				// 25. Phase
	std::string m_Mass;					// 26. Mass
	std::string m_EvasionRadius;		// 27. Evasion Radius
	std::string m_Skill;				// 28. Skill

private: // Item Box & Guide Box
	std::vector<RECT> m_vItemRect;
	std::vector<RECT> m_vItemGuideRect;

public:
	CUnitTool_UIViewer();
	~CUnitTool_UIViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	
	//====================================================
	// Member Function
	//====================================================

	static void funcSetupButton();
	static void funcRemoveButton();
	static void funcPlayerButton();

	void setupRegistFunc();

	static void funcMaxDPUP();
	static void funcMaxDPDown();
	static void funcCurrentDPUP();
	static void funcCurrentDPDown();
	static void funcRepairSpeedUP();
	static void funcRepairSpeedDown();
	static void funcRotateSpeedUP();
	static void funcRotateSpeedDown();
	static void funcAccelerateSpeedUP();
	static void funcAccelerateSpeedDown();
	static void funcMaxSpeedUP();
	static void funcMaxSpeedDown();
	static void funcCurrentSpeedUP();
	static void funcCurrentSpeedDown();
	static void funcRaderRangeUP();
	static void funcRaderRangeDown();
	static void funcAircraftCapacityUP();
	static void funcAircraftCapacityDown();
	static void funcPerformanceUP();
	static void funcPerformanceDown();
	static void funcSailorUP();
	static void funcSailorDown();
	static void funcAntiAirCraftCapacityUP();
	static void funcAntiAirCraftCapacityDown();
	static void funcAntiAirCraftRangeUP();
	static void funcAntiAirCraftRangeDown();
	static void funcAntiAirCraftDamageUP();
	static void funcAntiAirCraftDamageDown();
	static void funcMassUP();
	static void funcMassDown();
	static void funcEvasionRadiusUP();
	static void funcEvasionRadiusDown();

public:
	void setBeSetup(bool b)
	{
		m_bSetupShip = b;
	}
public:
	//====================================================
	// Setter Function
	//====================================================

	void setID(int id)
	{
		m_ID = std::to_string(id);
		m_vEditControl[0]->setEditText(m_ID);
	}
	void setTextureKey(std::string textureKey)
	{
		m_TextureKey = textureKey;
		m_vEditControl[1]->setEditText(m_TextureKey);
	}
	void setTopCount(int topCount)
	{
		m_TopCount = std::to_string(topCount);
		m_vEditControl[2]->setEditText(m_TopCount);
	}
	void setBodyCount(int bodyCount)
	{
		m_BodyCount = std::to_string(bodyCount);
		m_vEditControl[3]->setEditText(m_BodyCount);
	}
	void setBottomCount(int bottomCount)
	{
		m_BottomCount = std::to_string(bottomCount);
		m_vEditControl[4]->setEditText(m_BottomCount);
	}
	void setName(std::string name)
	{
		m_Name = name;
		m_vEditControl[5]->setEditText(m_Name);
	}
	void setShipType(std::string type)
	{
		m_ShipType = type;
		m_vEditControl[6]->setEditText(m_ShipType);
	}
	void setUnitType(std::string type)
	{
		m_UnitType = type;
		m_vEditControl[7]->setEditText(m_UnitType);
	}
	void setMaxDP(float maxDP)
	{
		m_MaxDP = std::to_string(maxDP);
		m_vEditControl[8]->setEditText(m_MaxDP);
	}
	void setCurrentDP(float currentDP)
	{
		m_CurrentDP = std::to_string(currentDP);
		m_vEditControl[9]->setEditText(m_CurrentDP);
	}
	void setRepairSpeed(float repairSpeed)
	{
		m_RepairSpeed = std::to_string(repairSpeed);
		m_vEditControl[10]->setEditText(m_RepairSpeed);
	}
	void setRotateSpeed(float rotateSpeed)
	{
		m_RotateSpeed = std::to_string(rotateSpeed);
		m_vEditControl[11]->setEditText(m_RotateSpeed);
	}
	void setAccelerateSpeed(float accelerateSpeed)
	{
		m_AccelerateSpeed = std::to_string(accelerateSpeed);
		m_vEditControl[12]->setEditText(m_AccelerateSpeed);
	}
	void setMaxSpeed(float maxSpeed)
	{
		m_MaxSpeed = std::to_string(maxSpeed);
		m_vEditControl[13]->setEditText(m_MaxSpeed);
	}
	void setCurrentSpeed(float currentSpeed)
	{
		m_CurrentSpeed = std::to_string(currentSpeed);
		m_vEditControl[14]->setEditText(m_CurrentSpeed);
	}
	void setRaderRange(float radarRange)
	{
		m_RaderRange = std::to_string(radarRange);
		m_vEditControl[15]->setEditText(m_RaderRange);
	}
	void setTurretCapacity(int capcity)
	{
		m_TurretCapacity = std::to_string(capcity);
		m_vEditControl[16]->setEditText(m_TurretCapacity);
	}
	void setTurretName(std::string turretName)
	{
		m_TurretName = turretName;
		m_vEditControl[17]->setEditText(m_TurretName);
	}
	void setAircraftCapacity(int capacity)
	{
		m_AircraftCapacity = std::to_string(capacity);
		m_vEditControl[18]->setEditText(m_AircraftCapacity);
	}
	void setPerformance(float performance)
	{
		m_Performance = std::to_string(performance);
		m_vEditControl[19]->setEditText(m_Performance);
	}
	void setSailor(int sailor)
	{
		m_Sailor = std::to_string(sailor);
		m_vEditControl[20]->setEditText(m_Sailor);
	}
	void setAntiAirCapacity(int capacity)
	{
		m_AntiAirCapacity = std::to_string(capacity);
		m_vEditControl[21]->setEditText(m_AntiAirCapacity);
	}
	void setAntiAirRange(float range)
	{
		m_AntiAirRange = std::to_string(range);
		m_vEditControl[22]->setEditText(m_AntiAirRange);
	}
	void setAntiAirDamage(float damage)
	{
		m_AntiAirDamage = std::to_string(damage);
		m_vEditControl[23]->setEditText(m_AntiAirDamage);
	}
	void setPhase(int phase)
	{
		m_Phase = std::to_string(phase);
		m_vEditControl[24]->setEditText(m_Phase);
	}
	void setMass(float mass)
	{
		m_Mass = std::to_string(mass);
		m_vEditControl[25]->setEditText(m_Mass);
	}
	void setEvasionRadius(float radius)
	{
		m_EvasionRadius = std::to_string(radius);
		m_vEditControl[26]->setEditText(m_EvasionRadius);
	}
	void setSkill(std::string skill)
	{
		m_Skill = skill;
		m_vEditControl[27]->setEditText(m_Skill);
	}

	//====================================================
	// Getter Function
	//====================================================

	std::string getID()
	{
		return m_ID;
	}
	std::string getTextureKey()
	{
		return m_TextureKey;
	}
	std::string getTopCount()
	{
		return m_TopCount;
	}
	std::string getBodyCount()
	{
		return m_BodyCount;
	}
	std::string getBottomCount()
	{
		return m_BottomCount;
	}
	std::string getName()
	{
		return m_Name;
	}
	std::string getShipType()
	{
		return m_ShipType;
	}
	std::string getUnitType()
	{
		return m_UnitType;
	}
	std::string getMaxDP()
	{
		return m_MaxDP;
	}
	std::string getCurrentDP()
	{
		return m_CurrentDP;
	}
	std::string getRepairSpeed()
	{
		return m_RepairSpeed;
	}
	std::string getRotateSpeed()
	{
		return m_RotateSpeed;
	}
	std::string getAccelerateSpeed()
	{
		return m_AccelerateSpeed;
	}
	std::string getMaxSpeed()
	{
		return m_MaxSpeed;
	}
	std::string getCurrentSpeed()
	{
		return m_CurrentSpeed;
	}
	std::string getRaderRange()
	{
		return m_RaderRange;
	}
	std::string getTurretCapacity()
	{
		return m_TurretCapacity;
	}
	std::string getTurretName()
	{
		return m_TurretName;
	}
	std::string getAircraftCapacity()
	{
		return m_AircraftCapacity;
	}
	std::string getPerformance()
	{
		return m_Performance;
	}
	std::string getSailor()
	{
		return m_Sailor;
	}
	std::string getAntiAirCapacity()
	{
		return m_AntiAirCapacity;
	}
	std::string getAntiAirRange()
	{
		return m_AntiAirRange;
	}
	std::string getAntiAirDamage()
	{
		return m_AntiAirDamage;
	}
	std::string getPhase()
	{
		return m_Phase;
	}
	std::string getMass()
	{
		return m_Mass;
	}
	std::string getEvasionRadius()
	{
		return m_EvasionRadius;
	}
	std::string getSkill()
	{
		return m_Skill;
	}
};

#endif // !_UNITTOOL_UIVIEWER_H
