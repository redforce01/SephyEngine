#ifndef _BATTLE_SHIP_H
#define _BATTLE_SHIP_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Ship;

#include <vector>
#include <string>
#include "Battle_UnitParser.h"

#include "entity.h"
#include "Battle_Turret.h"
#include "Battle_UI_ShipSelected.h"
#include "Battle_ShipUI_FleetMark.h"
#include "Battle_ShipUI_Indicator.h"
#include "Battle_ShipUI_State.h"
#include "Battle_DamageDigit.h"
#include "Battle_Operator.h"
#include "Battle_ShipTailEffect.h"

namespace battleShipTextureNS
{
	const std::string TEXTURE_KEY_TOP			= "Top_";
	const std::string TEXTURE_KEY_BODY			= "Body_";
	const std::string TEXTURE_KEY_BOTTOM		= "Bottom_";
	const std::string TEXTURE_KEY_WAVE			= "Wave_";
	const std::string TEXTURE_KEY_SHADOW		= "Shadow_";
	const std::string TEXTURE_KEY_SUNKEN		= "Sunken_";
	const std::string TEXTURE_KEY_SUNKEN_SHADOW = "Sunkenshadow_";
	const UINT SHIP_SUNKEN_MAX_FRAME = 10;

	const COLOR_ARGB SHIP_SHADOW_COLOR = SETCOLOR_ARGB(128, 32, 32, 32);
	const COLOR_ARGB SHIP_SUNKEN_SHADOW_COLOR = SETCOLOR_ARGB(64, 64, 64, 64);
}

namespace battleShipGeneralNS
{
	const std::string ERROR_MESSAGE = "Battle Ship Initialized Failed";

	const UINT SHIP_WAVE_TEXTURE_COUNT			= 1;
	const UINT SHIP_SHADOW_TEXTURE_COUNT		= 1;
	const UINT SHIP_SUNKEN_TEXTURE_COUNT		= 1;
	const UINT SHIP_SUNKEN_SHADOW_TEXTURE_COUNT = 1;

	const float SHIP_ENTITY_TEXTURE_SCALE = 0.75f;

	// WAVE + SHADOW + SUNKEN + SUNKEN SHADOW
	const UINT SHIP_BASIC_TEXTURE_COUNT = 
		SHIP_WAVE_TEXTURE_COUNT + SHIP_SHADOW_TEXTURE_COUNT + 
		SHIP_SUNKEN_TEXTURE_COUNT + SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;

	const float SHIP_SUNKEN_SPRITE_CHANGE_TIME_EARLY = 5.0f;
	const float SHIP_SUNKEN_SPRITE_CHANGE_TIME_LATE = 30.0f;
	const float BATTLEMAP_OUTLINE_REVERSING_DISTANCE = 200.f;

	//===============================================
	// Set Off Sound Check Time
	//===============================================
	const float UNDETECTED_SOUND_TIME = 10.f;
	const float UNATTACKED_SOUND_TIME = 3.0f;
	const UINT SHIP_TAIL_EFFECT_SIZE = 30;
}

//===============================================
// Enum Class UNIT_TYPE
//  + UNIT SMALL | UNIT_MEDIUM | UNIT_HEAVY | UNIT_ULTRA
//===============================================
enum class UNIT_TYPE
{ SHIP_UNIT_TYPE_SMALL, SHIP_UNIT_TYPE_MEDIUM, SHIP_UNIT_TYPE_HEAVY, SHIP_UNIT_TYPE_ULTRA };

//===============================================
// Enum Class UNIT_TYPE
//  + SHIP_CC | SHIP_FF | SHIP_DD | SHIP_CL | SHIP_CA | SHIP_BB | SHIP_CV
//===============================================
enum class SHIP_TYPE
{ SHIP_CC, SHIP_TYPE_FF, SHIP_TYPE_DD, SHIP_TYPE_CL, SHIP_TYPE_CA, SHIP_TYPE_BB, SHIP_TYPE_CV };

//===============================================
// Enum Class UNIT_TYPE
//  + ...
//===============================================
enum class BUF_DEBUF_EVENT {};

//===============================================
// Enum Class QUDRANT_TYPE
//  + QUDRANT_RIGHT_TOP		: 0 (mean = x,y graph 1 qudrant)
//  + QUDRANT_LEFT_TOP		: 1	(mean = x,y graph 2 qudrant)
//  + QUDRANT_LEFT_BOTTOM	: 2	(mean = x,y graph 3 qudrant)
//	+ QUDRANT_RIGHT_BOTTOM	: 3	(mean = x,y graph 4 qudrant)
//===============================================
enum class QUDRANT_TYPE	
{ QUDRANT_RIGHT_TOP, QUDRANT_LEFT_TOP, QUDRANT_LEFT_BOTTOM, QUDRANT_RIGHT_BOTTOM };

//===============================================
// Forward Declaration Class List
//===============================================
class CBattle_MapSystem;
class CBattle_UnitSystem;
class CUnitTool_UnitControlSystem;
class CUnitTool_UnitMapSystem;

//===============================================
// CBattle_Ship Class
//===============================================
class CBattle_Ship
{	
private: // Forward Declarations - For Battle
	CBattle_MapSystem* m_pBattleMapSystem;
	CBattle_UnitSystem* m_pBattleUnitSystem;
public:
	void setMemoryLinkBattleMapSystem(CBattle_MapSystem* pBattleMapSystem)
	{
		m_pBattleMapSystem = pBattleMapSystem;
	}
	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}
	CBattle_UnitSystem* getBattleUnitSystem() const
	{
		return m_pBattleUnitSystem;
	}
private: // Forward Declarations - For UnitTool
	CUnitTool_UnitControlSystem* m_pUnitControlSystem;
	CUnitTool_UnitMapSystem* m_pUnitMapSystem;
	bool m_bUnitToolMode;
public:
	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pUnitControlSystem = pUnitControlSystem;
	}
	void setMemoryLinkUnitToolMapSystem(CUnitTool_UnitMapSystem* pUnitToolMapSystem)
	{
		m_pUnitMapSystem = pUnitToolMapSystem;
	}
	CUnitTool_UnitControlSystem* getUnitToolUnitControlSystem() const
	{
		return m_pUnitControlSystem;
	}
	void setUnitToolMode(bool bUnitToolMode)
	{
		m_bUnitToolMode = bUnitToolMode;
	}

private: // typedef
	typedef std::vector<CBattle_Turret*>			vTurrets;		// mean : vector<Turret*>	
	typedef std::vector<std::pair<bool, Entity*>>	vShipParts;		// mean : vector<pair<physics flag(bool), ShipParts*(Entity*)>
private:
	Game*		m_pGame;
	Graphics*	m_pGraphics;	// Graphics Pointer - For Rendering
	Input*		m_pInput;		// Input Pointer	- For Selecting & Ordering
public:
	Game* getGamePtr() const
	{
		return m_pGame;
	}
private:
	//===============================================
	// Units Variables 
	//===============================================
	int			m_nUnitUniqueID;			// Unit Unique ID
	int			m_nUnitID;					// Unit ID
	std::string m_strName;					// Unit Name
	std::string m_strTextureKey;			// Unit Texture Key
	//===============================================
	int			m_nSpriteTopCount;			// Unit[Ship] Texture Top Count
	int			m_nSpriteBodyCount;			// Unit[Ship] Texture Body Count
	int			m_nSpriteBottomCount;		// Unit[Ship] Texture Bottom Count
	//===============================================
	int			m_nSpriteTopStart;			// Unit Top Sprite Start Number
	int			m_nSpriteBodyStart;			// Unit Body Sprite Start Number
	int			m_nSpriteBottomStart;		// Unit Bottom Sprite Start Number
	int			m_nSpriteShadowStart;		// Unit Shadow Sprite Start Number
	int			m_nSpriteWaveStart;			// Unit Wave Sprite Start Number
	int			m_nSpriteSunkenStart;		// Unit Sunken Sprite Start Number
	int			m_nSpriteSunkenShadowStart;	// Unit SunkenShadow Sprite Start Number
	//===============================================
	// These String Variables Help to Make Sprite Texture Key
	//  + example) 
	//		std::string result
	//		result = m_strSpriteWaveKey + std::to_string(m_nSpriteWaveNum)
	//		setSpriteImage(IMAGEMANGE->getTexture(result))
	//  + These Codes able to Easily update Sprite change Function
	//===============================================
	std::vector<std::string> m_vSpriteTopKey;	  // Unit Real Texture Top Key
	std::vector<std::string> m_vSpriteBodyKey;	  // Unit Real Texture Body Key
	std::vector<std::string> m_vSpriteBottomKey;  // Unit Real Texture Bottom Key
	std::string m_strSpriteShadowKey;			  // Unit Real Texture Shadow Key
	std::string m_strSpriteWaveKey;				  // Unit Real Texture Wave Key
	std::string m_strSpriteSunkenKey;			  // Unit Real Texture Sunken Key
	std::string m_strSpriteSunkenShadowKey;		  // Unit Real Texture SunkenShadow Key
	//===============================================
	int			m_nSpriteShipTopNum;			// Unit Current Ship Top Sprite Number
	int			m_nSpriteShipBodyNum;			// Unit Current Ship Body Sprite Number
	int			m_nSpriteShipBottomNum;			// Unit Current Ship Bottom Sprite Number
	int			m_nSpriteShipShadowNum;			// Unit Current Ship Shadow Sprite Number
	int			m_nSpriteShipWaveNum;			// Unit Current Ship Wave Sprite Number
	int			m_nSpriteShipWaveRotateNum;		// Unit Current Ship Wave Sprite Rotation Number
	int			m_nSpriteSunkenNum;				// Unit Current Ship Sunken Sprite Number
	int			m_nSpriteSunkenShadowNum;		// Unit Current Ship Sunken Shadow Sprite Number
	//================================================
	std::string m_strShipType;				// Unit Type
	float		m_fTargetX;					// Unit Target X
	float		m_fTargetY;					// Unit Target Y
	float		m_fCurrentHealth;			// Unit Current HP
	float		m_fMaxHealth;				// Unit Max HP
	float		m_fRepairSpeed;				// Unit Current Repair Speed
	float		m_fRepairSpeedOriginal;		// Unit Original Repair Speed
	float		m_fCurrentAngle;			// Unit Current Angle In Radians
	float		m_fTargetAngle;				// Unit Target Angle In Radians
	float		m_fRotateSpeed;				// Unit Rotate Speed
	float		m_fCurrentSpeed;			// Unit Move Speed
	float		m_fMaxSpeed;				// Unit Max Speed
	float		m_fAccelateSpeed;			// Unit Accelerate Speed
	float		m_fRaderRange;				// Unit Sight Range
	float		m_fPerformance;				// Unit Performance Count (mean : battle power)
	int			m_nSailorCount;				// Unit Sailor Count
	int			m_nTurretCount;				// Unit Turret Count
	std::string m_strTurretID;				// Unit Turret ID
	vTurrets	m_vTurret;					// Unit Turret Vector
	float		m_nAntiAirTurrectCount;		// Unit AntiAir Turret Count
	float		m_fAntiAirRange;			// Unit AntiAir Turret Range
	float		m_fAntiAirDamage;			// Unit AntiAir Turret Damage
	int			m_nAirCraftCapacity;		// Unit AirCraft Capacity
	int			m_nCallPhase;				// Unit CallPhase Number
	float		m_fMass;					// Unit Mass ( Unit Real Weight )	
	float		m_fEvasionRange;			// Unit Evasion
	//================================================
	bool			m_bIncludedFleet;		// Ship Included Fleet
	int				m_nFleetNumber;			// Ship Fleet Number
	float			m_fDistanceFromFleet;	// Ship Distance From Fleet
	float			m_fAngleFromFleet;		// Ship Angle From Fleet
	CBattle_Ship*	m_pFlagShip;			// Ship - FlagShip Connected Pointer (it would be connected when this ship is not flagShip)
	float			m_fFormationX;			// m_fFormationX = cos(m_fAngleFromFleet) * m_fDistanceFromFleet + m_pFlagShip->getCurrentCenterX()
	float			m_fFormationY;			// m_fFormationY = -sin(m_fAngleFromFleet) * m_fDistanceFromFleet + m_pFlagShip->getCurrentCenterY()
	float			m_fFleetMaxSpeed;		// Fleet Max Speed ( Top Slowly Ship Speed In Fleet : ex) cv speed - 20, ff speed - 44 == FleetMaxSpeed : 20 )
	//================================================
	std::string m_strShipRankMark;			// Ship Rank Mark FileName
	
private:
	std::vector<CBattle_ShipTailEffect> m_vTailEffect;
private:
	bool m_bFixedEngine;
public:
	void setFixedEngineOnOff(bool bOnOff)
	{
		m_bFixedEngine = bOnOff;
	}
	bool getFixedEngineOnOff() const
	{
		return m_bFixedEngine;
	}
private:
	bool m_bAutoGunOnOff;
	bool m_bAutoAAGunOnOff;
public:
	void setAutoGunOnOff(bool bGunOnOff)
	{
		m_bAutoGunOnOff = bGunOnOff;
	}
	bool getAutoGunOnOff() const
	{
		return m_bAutoGunOnOff;
	}
	void setAutoAAGunOnOff(bool bAAGunOnOff)
	{
		m_bAutoAAGunOnOff = bAAGunOnOff;
	}
	bool getAutoAAGunOnOff() const
	{
		return m_bAutoAAGunOnOff;
	}

private: // Ship Detected Code - For Ship vs Ship with RaderRange
	bool m_bDetected;
	bool m_bDetectedSound;
	float m_fUnDetectedTime;
public:
	void setDetected(bool bDetected)
	{
		m_bDetected = bDetected;
	}
	bool getDetected() const
	{
		return m_bDetected;
	}
	void setDetectedSound(bool bDetectedSound)
	{
		m_bDetectedSound = bDetectedSound;
	}
	bool getDetectedSound() const
	{
		return m_bDetectedSound;
	}
private:
	bool m_bAttacked;
	bool m_bAttackedSound;
	float m_fUnattackedTime;
public:
	void setAttacked(bool bAttacked)
	{
		m_bAttacked = bAttacked;
	}
	bool getAttacked() const
	{
		return m_bAttacked;
	}
	void setAttackedSound(bool bAttackedSound)
	{
		m_bAttackedSound = bAttackedSound;
	}
	bool getAttackedSound() const
	{
		return m_bAttackedSound;
	}
private:
	bool m_bSukenStart;
	bool m_bSunkenComplete;
	float m_fSunkenDeltaTime;
	std::string m_strSukenSoundName;
public:
	bool getSunkenComplete() const
	{
		return m_bSunkenComplete;
	}
private:
	//===============================================
	// enum class Type Variables
	//===============================================
	UNIT_TYPE m_eUnitType;			// enum_class Unit Type
	SHIP_TYPE m_eShipType;			// enum_class Ship Type
	BUF_DEBUF_EVENT m_eBufEvent;	// enum_class Event Type

private:
	//===============================================
	// Ship Entity Vector
	//  + arrShipParts : typedef std::vector<std::pair<bool, Entity*>>
	//  + All Units has Each Entity Parts
	//  + The bool is meaning Physics Flag
	//  + The Entity is Real Unit Entity
	//   - Entity Class is SomeThings about Physics
	//  + if The bool == true ? Physics Entity : NoPhysics Entity
	//  + Original : std::vector<std::pair<bool, Entity*>>
	//===============================================
	vShipParts m_vEntity;
	vShipParts m_vRealParts;
public:
	vShipParts getShipEntity() const
	{
		return m_vEntity;
	}
	vShipParts getShipRealParts() const
	{
		return m_vRealParts;
	}

private:
	// TouchData :  mean = Circle Data For UnitSelect
	struct tagTouch
	{
		float x, y;
		float radius;
	};
	// Collision : mean = Circle Data for Unit Collision Pre Detect
	struct tagCollision
	{
		float x, y;
		float radius;
	};
	struct tagRader
	{
		float x, y;
		float radius;
	};
	struct tagEvasion
	{
		float x, y;
		float radius;
	};
private:
	tagTouch		m_stUnitTouch;		// For Unit Clicekd TouchData
	tagCollision	m_stUnitCollision;	// For Unit Collision
	tagRader		m_stRader;			// For Unit Rader Collision
	tagEvasion		m_stEvasion;		// For Unit Attacked Collision
public:
	void updateTagDataPos(float centerX, float centerY)
	{
		m_stUnitTouch.x		= centerX;
		m_stUnitTouch.y		= centerY;
		m_stUnitCollision.x = centerX;
		m_stUnitCollision.y = centerY;
		m_stRader.x			= centerX;
		m_stRader.y			= centerY;
		m_stEvasion.x		= centerX;
		m_stEvasion.y		= centerY;
	}
	void updateTagDataX(float x)
	{
		m_stUnitTouch.x = x;
		m_stUnitCollision.x = x;
		m_stRader.x = x;
	}
	void updateTagDataY(float y)
	{
		m_stUnitTouch.y = y;
		m_stUnitCollision.y = y;
		m_stRader.y = y;
	}
	void setupRaderRadius(float radius)
	{
		m_stRader.radius = radius;
	}
	void setupEvasionRadius(float radius)
	{
		m_stEvasion.radius = radius;
	}

	// Get Ship TouchData( struct { float x, y, radius } )
	// TouchData :  mean = Circle Data For UnitSelect
	tagTouch getShipTouchData() const
	{
		return m_stUnitTouch;
	}
	tagCollision getShipCollision() const
	{
		return m_stUnitCollision;
	}
	tagRader getShipRaderCollision() const
	{
		return m_stRader;
	}
	tagEvasion getShipEvasionCollision() const
	{
		return m_stEvasion;
	}
private: // UNIT DATA PARSER
	CBattle_UnitParser m_UnitDataParser; 

private: // SHIP UI
	CBattle_ShipUI_FleetMark	m_BattleShipUI_FleetMark;
	CBattle_UI_ShipSelected		m_BattleShipUI_Selected;
	CBattle_ShipUI_Indicator	m_BattleShipUI_Indicator;
	CBattle_ShipUI_State		m_BattleShipUI_State;
private:
	bool m_bPlayerShip;
	bool m_bInitialized;
	bool m_bActive;
	bool m_bDestroy; // Unit Destroyed Flag
	bool m_bDestroyAnimeComplete;
	bool m_bChangeSprite;
	bool m_bSelected;
	bool m_bArrived;
	bool m_bIntersect;
	bool m_bFlagShip;
	//===============================================
	bool m_bDebug;
	bool m_bDummy;

public:
	CBattle_Ship();
	virtual ~CBattle_Ship();

	//===============================================
	// Ship Member Functions
	//===============================================

	//===============================================
	// CBattle_Ship Initialize
	//  + Parameter 1 ( Game* gamePtr )			- For Entity Initialize
	//  + Parameter 2 ( std::string shipName )	- For ShipData Parsing = SHIP FILE NAME
	//===============================================
	bool initialize(Game* gamePtr, std::string shipName);
	//===============================================
	// CBattle_Ship Update
	//  + Unit Sprite Animation Update
	//  + ...
	//===============================================
	void update(float frameTime);
	//===============================================
	// CBattle_Ship Render
	//  + Unit Animation Rendering
	//  + ...
	//===============================================
	void render();
	//===============================================
	// CBattle_Ship ai
	//  + ...
	//===============================================
	void ai();
	//===============================================
	// CBattle_Ship collision
	//  + ...
	//===============================================
	void collision();

private:
	//===============================================
	// Movement Update
	//  + Ship Rotate->return bool(true -> update sprite)
	//  + Ship Engine
	//  + Ship Movement
	//===============================================
	void updateMovement(float frameTime);
	void updateEngine(float frameTime);
	bool updateRotate(float frameTime);
	//===============================================
	// Repair Update
	//  + ShipHealth += Ship Repairspeed * frameTime
	//===============================================
	void updateRepair(float frameTime);
	//===============================================
	// Sprite Update
	//  + Update Only Normal Sprite (Alive)
	//  + Update Sunken Sprite (Destroyed)
	//===============================================
	void updateSprite(float frameTime);
	void updateShipSprite();
	void updateWaveSprite();
	void updateSunkenSprite(float frameTime);
	//===============================================
	// Turret Update
	//  + Auto Targeting
	//===============================================
	void updateTurret(float frameTime);

	//===============================================
	// Sound Update 
	//  + Detected Sound Update
	//  + Damaged Sound Update
	//===============================================
	void updateUndetectedSound(float frameTime);
	void updateAttackedSound(float frameTime);

	void playSoundDamagedOperator();
private:
	void setupShipDataFormat(std::vector<std::string> vArray);
	bool setupEntity(Game* gamePtr, std::string strImageName, bool bPhysics);

public:
	//===============================================
	// Member Functions
	//===============================================

	void moveX(float fDistance);
	void moveY(float fDistance);

	void resetShipFleetData()
	{
		setFlagShip(false);
		setFleetIncluded(false);
		setFleetAngleFromFlagShip(0.f);
		setFleetDistanceFromFlagShip(0.f);
		setFleetNumber(-1);
	}

	void setDummyShip(bool bDummy)
	{
		m_bDummy = bDummy;
	}

	bool getDummyShip() const
	{
		return m_bDummy;
	}
	
	//===============================================
	// Hit damage Function
	//  + Send Damage
	//  + Sound Play
	//===============================================
	void HitDamage(float damage);
	
	//===============================================
	// Take Buff Functions
	//===============================================
		
	void takeRepairBuf(bool bTakeOnOff, float bufSpeed = 0.f);
	
	
	//===============================================
	// Setter Functions
	//===============================================

	void setShipUniqueID(int id)
	{
		m_nUnitUniqueID = id;
	}

	void setTargetPos(VECTOR2 target)
	{
		m_fTargetX = target.x;
		m_fTargetY = target.y;
		setShipArrived(false);
	}

	void setUnitSelected(bool bSelected)
	{
		m_bSelected = bSelected;
		m_BattleShipUI_Selected.setActive(bSelected);
	}
		
	void getShipBufEventEnum(BUF_DEBUF_EVENT enEvent)
	{
		m_eBufEvent = enEvent;
	}
		
	void setCurrentX(float posX)
	{
		for (auto iter : m_vEntity)
		{
			iter.second->setX(posX);
		}
		m_fTargetX = m_vEntity[0].second->getCenterX();
		updateTagDataX(posX + m_vEntity[0].second->getWidth() / 2);
		m_BattleShipUI_Selected.setUIPosX(m_vEntity[0].second->getCenterX());
		m_BattleShipUI_Indicator.setUIPos();
		m_BattleShipUI_FleetMark.setUIPos();
		m_BattleShipUI_State.setupStateUIPos();
	}

	void setCurrentY(float posY)
	{
		for (auto iter : m_vEntity)
		{
			iter.second->setY(posY);
		}
		m_fTargetY = m_vEntity[0].second->getCenterY();
		updateTagDataY(posY + m_vEntity[0].second->getHeight() / 2);
		m_BattleShipUI_Selected.setUIPosY(m_vEntity[0].second->getCenterY());
		m_BattleShipUI_Indicator.setUIPos();
		m_BattleShipUI_FleetMark.setUIPos();
		m_BattleShipUI_State.setupStateUIPos();
	}

	void setCurrentCenterX(float centerX)
	{
		auto shipWidth = m_vEntity[0].second->getWidth();
		for (auto iter : m_vEntity)
		{
			iter.second->setX(centerX - (shipWidth / 2));
		}
		m_fTargetX = m_vEntity[0].second->getCenterX();
		updateTagDataX(centerX - (shipWidth / 2));
		m_BattleShipUI_Selected.setUIPosX(m_vEntity[0].second->getCenterX());
		m_BattleShipUI_Indicator.setUIPos();
		m_BattleShipUI_FleetMark.setUIPos();
		m_BattleShipUI_State.setupStateUIPos();
	}

	void setCurrentCenterY(float centerY)
	{
		auto shipHeight = m_vEntity[0].second->getHeight();
		for (auto iter : m_vEntity)
		{
			iter.second->setY(centerY - (shipHeight / 2));
		}
		m_fTargetY = m_vEntity[0].second->getCenterY();
		updateTagDataY(centerY - (shipHeight / 2));
		m_BattleShipUI_Selected.setUIPosY(m_vEntity[0].second->getCenterY());
		m_BattleShipUI_Indicator.setUIPos();
		m_BattleShipUI_FleetMark.setUIPos();
		m_BattleShipUI_State.setupStateUIPos();
	}

	void setTargetX(float targetX)
	{
		m_fTargetX = targetX;
		setShipArrived(false);
	}

	void setTargetY(float targetY)
	{
		m_fTargetY = targetY;
		setShipArrived(false);
	}

	void setCurrentHealth(float fHealth)
	{
		m_fCurrentHealth = fHealth;
	}

	void setMaxHealth(float fMaxHealth)
	{
		m_fMaxHealth = fMaxHealth;
	}

	void setRepairSpeed(float fRepairSpeed)
	{
		m_fRepairSpeed = fRepairSpeed;
	}

	void setCurrentAngle(float fAngle)
	{
		m_fCurrentAngle = fAngle;
	}

	void setTargetAngle(float fAngle)
	{
		m_fTargetAngle = fAngle;
	}

	void setRotateSpeed(float fRotSpeed)
	{
		m_fRotateSpeed = fRotSpeed;
	}

	void setCurrentSpeed(float fSpeed)
	{
		m_fCurrentSpeed = fSpeed;
	}

	void setMaxSpeed(float fMaxSpeed)
	{
		m_fMaxSpeed = fMaxSpeed;
	}

	void setAccelateSpeed(float fAccelSpeed)
	{
		m_fAccelateSpeed = fAccelSpeed;
	}

	void setRaderRange(float fRaderRange)
	{
		m_fRaderRange = fRaderRange;
		setupRaderRadius(m_fRaderRange);
	}

	void setPerformance(float fPerformance)
	{
		m_fPerformance = fPerformance;
	}

	void setSailorCount(float nSailorCount)
	{
		m_nSailorCount = nSailorCount;
	}
	
	void setAntiAirTurretCount(int nTurretCount)
	{
		m_nAntiAirTurrectCount = nTurretCount;
	}

	void setAntiAirRange(float fRange)
	{
		m_fAntiAirRange = fRange;
	}

	void setAntiAirDamage(float fDamage)
	{
		m_fAntiAirDamage = fDamage;
	}

	void setAirCraftCapacity(int nAirCraftCapacity)
	{
		m_nAirCraftCapacity = nAirCraftCapacity;
	}
		
	void setShipMass(float fMass)
	{
		m_fMass = fMass;
	}

	void setEvasion(float fEvasion)
	{
		m_fEvasionRange = fEvasion;
		setupEvasionRadius(m_fEvasionRange);
	}

	void setFleetIncluded(bool bIncluded)
	{
		m_bIncludedFleet = bIncluded;		
	}

	void setFleetNumber(int nFleetNumber)
	{
		m_BattleShipUI_FleetMark.setFleetMarkNumber(nFleetNumber);
		m_nFleetNumber = nFleetNumber;
	}

	void setFleetDistanceFromFlagShip(float fDistance)
	{
		m_fDistanceFromFleet = fDistance;
	}

	void setFleetAngleFromFlagShip(float fAngle) // : radian
	{
		m_fAngleFromFleet = fAngle;
	}

	void setFleetConnectFlagShip(CBattle_Ship* pFlagShip)
	{
		if (pFlagShip == nullptr)
			return;

		auto flagShipX = pFlagShip->getCurrentCenterX();
		auto flagShipY = pFlagShip->getCurrentCenterY();
		auto thisShipX = this->getCurrentCenterX();
		auto thisShipY = this->getCurrentCenterY();

		auto fDistanceFromFlagShip = MyUtil::getDistance(flagShipX, flagShipY, thisShipX, thisShipY);
		auto fAngleFromFlagShip = MyUtil::getAngle(flagShipX, flagShipY, thisShipX, thisShipY);
		m_fDistanceFromFleet = fDistanceFromFlagShip;
		m_fAngleFromFleet = fAngleFromFlagShip;

		m_pFlagShip = pFlagShip;
	}

	void setPlayerShip(bool bPlayerShip)
	{
		m_bPlayerShip = bPlayerShip;
		m_BattleShipUI_State.setPlayerColorable(bPlayerShip);
	}

	void setShipArrived(bool bArrived)
	{
		m_bArrived = bArrived;
	}

	void setShipActive(bool bActive)
	{
		m_bActive = bActive;
	}

	void setFlagShip(bool bFlagShip)
	{
		m_bFlagShip = bFlagShip;
	}

	void setShipColorFilter(COLOR_ARGB color)
	{
		for (auto iter : m_vEntity)
		{
			iter.second->setColorFilter(color);
		}
	}

	void setDebugMode(bool bDebug)
	{
		m_bDebug = bDebug;
	}

	//===============================================
	// Getter Functions
	//===============================================

	int getShipUniqueID() const
	{
		return m_nUnitUniqueID;
	}



	// Get Ship Entities
	std::vector<std::pair<bool, Entity*>> getShipParts() const
	{
		return m_vEntity;
	}

	UNIT_TYPE getUnitTypeEnum() const
	{
		return m_eUnitType;
	}

	SHIP_TYPE getShipTypeEnum() const
	{
		return m_eShipType;
	}

	BUF_DEBUF_EVENT getShipBufEventEnum() const
	{
		return m_eBufEvent;
	}
	
	int getShipID() const
	{
		return m_nUnitID;
	}

	std::string getShipName() const
	{
		return m_strName;
	}

	std::string getTextureKey() const
	{
		return m_strTextureKey;
	}

	std::string getShipType() const
	{
		return m_strShipType;
	}

	float getCurrentX() const
	{
		return m_vEntity[0].second->getX();
	}

	float getCurrentY() const
	{
		return m_vEntity[0].second->getY();
	}

	float getCurrentCenterX() const
	{
		return m_vEntity[0].second->getCenterX();
	}

	float getCurrentCenterY() const
	{
		return m_vEntity[0].second->getCenterY();
	}

	float getTargetX() const
	{
		return m_fTargetX;
	}

	float getTargetY() const
	{
		return m_fTargetY;
	}

	float getCurrentHealth() const
	{
		return m_fCurrentHealth;
	}

	float getMaxHealth() const
	{
		return m_fMaxHealth;
	}

	float getRepairSpeed() const
	{
		return m_fRepairSpeed;
	}

	float getCurrentAngle() const
	{
		return m_fCurrentAngle;
	}

	float getTargetAngle() const
	{
		return m_fTargetAngle;
	}

	float getRotateSpeed() const
	{
		return m_fRotateSpeed;
	}

	float getCurrentSpeed() const
	{
		return m_fCurrentSpeed;
	}

	float getMaxSpeed() const
	{
		return m_fMaxSpeed;
	}

	float getAccelateSpeed() const
	{
		return m_fAccelateSpeed;
	}

	float getRaderRange() const
	{
		return m_fRaderRange;
	}

	float getPerformance() const
	{
		return m_fPerformance;
	}

	int getSailorCount() const
	{
		return m_nSailorCount;
	}

	int getTurretCount() const
	{
		return m_nTurretCount;
	}

	std::string getTurretID() const
	{
		return m_strTurretID;
	}

	std::vector<CBattle_Turret*> getTurrets() const
	{
		return m_vTurret;
	}

	float getAntiAirTurretCount() const
	{
		return m_nAntiAirTurrectCount;
	}

	float getAntiAirRange() const
	{
		return m_fAntiAirRange;
	}

	float getAntiAirDamage() const
	{
		return m_fAntiAirDamage;
	}

	int getAirCraftCapacity() const
	{
		return m_nAirCraftCapacity;
	}

	int getCallPhase() const
	{
		return m_nCallPhase;
	}

	float getShipMass() const
	{
		return m_fMass;
	}

	float getEvasion() const
	{
		return m_fEvasionRange;
	}

	bool getFleetIncluded() const
	{
		return m_bIncludedFleet;
	}

	int getFleetNumber() const
	{
		return m_nFleetNumber;
	}

	float getFleetDistanceFromFlagShip() const
	{
		return m_fDistanceFromFleet;
	}

	float getFleetAngleFromFlagShip() const
	{
		return m_fAngleFromFleet;
	}

	CBattle_Ship* getFleetConnectFlagShip() const
	{
		return m_pFlagShip;
	}

	bool getIsPlayerShip() const
	{
		return m_bPlayerShip;
	}

	bool getShipSelected() const
	{
		return m_bSelected;
	}

	bool getShipActive() const
	{
		return m_bActive;
	}

	bool getShipDestroy() const
	{
		return m_bDestroy;
	}

	bool getShipArrived() const
	{
		return m_bArrived;
	}

	// This Getter Function Would return First Entity's Width
	float getShipWidth() const
	{
		return m_vEntity[0].second->getWidth();
	}

	// This Getter Function Would return First Entity's Height
	float getShipHeight() const
	{
		return m_vEntity[0].second->getHeight();
	}

	bool getFlagShip() const
	{
		return m_bFlagShip;
	}

	int getTopSpriteCount() const
	{
		return m_nSpriteTopCount;
	}
	int getBodySpriteCount() const
	{
		return m_nSpriteBodyCount;
	}
	int getBottomSpriteCount() const
	{
		return m_nSpriteBottomCount;
	}

	bool getDebugMode() const
	{
		return m_bDebug;
	}

	std::string getShipRankMark() const
	{
		return m_strShipRankMark;
	}
};

#endif // !_BATTLE_UNIT_H