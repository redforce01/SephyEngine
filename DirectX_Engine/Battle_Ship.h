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

namespace battleShipTextureNS
{
	const std::string TEXTURE_KEY_TOP			= "Top_";
	const std::string TEXTURE_KEY_BODY			= "Body_";
	const std::string TEXTURE_KEY_BOTTOM		= "Bottom_";
	const std::string TEXTURE_KEY_WAVE			= "Wave_";
	const std::string TEXTURE_KEY_SHADOW		= "Shadow_";
	const std::string TEXTURE_KEY_SUNKEN		= "Sunken_";
	const std::string TEXTURE_KEY_SUNKEN_SHADOW = "Sunkenshadow_";

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
enum class QUDRANT_TYPE	
{ QUDRANT_RIGHT_TOP, QUDRANT_LEFT_TOP, QUDRANT_LEFT_BOTTOM, QUDRANT_RIGHT_BOTTOM };

class CBattle_Ship
{	
private: // typedef
	typedef std::vector<CBattle_Turret*>			vTurrets;		// mean : vector<Turret*>	
	typedef std::vector<std::pair<bool, Entity*>>	vShipParts;		// mean : vector<pair<physics flag(bool), ShipParts*(Entity*)>
private:
	Graphics*	m_pGraphics;	// Graphics Pointer - For Rendering
	Input*		m_pInput;		// Input Pointer	- For Selecting & Ordering
private:
	//===============================================
	// Units Variables 
	//===============================================
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
	std::string m_strShipType;				// UNIT Type
	float		m_fTargetX;					// Unit Target X
	float		m_fTargetY;					// Unit Target Y
	float		m_fCurrentHealth;			// Unit Current HP
	float		m_fMaxHealth;				// Unit Max HP
	float		m_fRepairSpeed;				// Unit Repair Speed
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
	//================================================
	bool		m_bIncludedFleet;			// Ship Included Fleet
	int			m_nFleetNumber;				// Ship Fleet Number
	float		m_fDistanceFromFleet;		// Ship Distance From Fleet
	float		m_fAngleFromFleet;			// Ship Angle From Fleet
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

private:
	// TouchData :  mean = Circle Data For UnitSelect
	struct tagTouch
	{
		float x, y;
		float radius;
	};
private:
	tagTouch m_stUnitTouch;	// For Unit Clicekd TouchData

private:
	CBattle_UnitParser m_UnitDataParser; // UNIT DATA PARSER
	CBattle_UI_ShipSelected m_BattleUIShipSelected;
private:
	bool m_bInitialized;
	bool m_bActive;
	bool m_bDestroy; // Unit Destroyed Flag
	bool m_bDestroyAnimeComplete;
	bool m_bChangeSprite;
	bool m_bSelected;
	bool m_bArrived;
	bool m_bFixedEngine;
	//===============================================
	bool m_bDebug;

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
	void updateTouchData();
	void updateMovement(float frameTime);
	void updateEngine(float frameTime);
	bool updateRotate(float frameTime);
	void updateRepair(float frameTime);
	void updateSprite();
	void updateShipSprite();
	void updateWaveSprite();
	void updateSunkenSprite();

private:
	void setupShipDataFormat(std::vector<std::string> vArray);
	bool setupEntity(Game* gamePtr, std::string strImageName, bool bPhysics);

public:
	//===============================================
	// Member Functions
	//===============================================

	void moveX(float fDistance);
	void moveY(float fDistance);

	//===============================================
	// Setter Functions
	//===============================================

	void setTargetPos(VECTOR2 target)
	{
		m_fTargetX = target.x;
		m_fTargetY = target.y;
		setShipArrived(false);
	}

	void setUnitSelected(bool bSelected)
	{
		m_bSelected = bSelected;
		m_BattleUIShipSelected.setActive(bSelected);
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
		m_BattleUIShipSelected.setUIPosX(m_vEntity[0].second->getCenterX());
	}

	void setCurrentY(float posY)
	{
		for (auto iter : m_vEntity)
		{
			iter.second->setY(posY);
		}
		m_fTargetY = m_vEntity[0].second->getCenterY();
		m_BattleUIShipSelected.setUIPosY(m_vEntity[0].second->getCenterY());
	}

	void setTargetX(float targetX)
	{
		m_fTargetX = targetX;
	}

	void setTargetY(float targetY)
	{
		m_fTargetY = targetY;
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

	void getAntiAirRange(float fRange)
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

	void setFleetNumber(int nFleetNumber)
	{
		m_nFleetNumber = nFleetNumber;
	}

	void setShipArrived(bool bArrived)
	{
		m_bArrived = bArrived;
	}

	void setShipActive(bool bActive)
	{
		m_bActive = bActive;
	}

	//===============================================
	// Getter Functions
	//===============================================

	// Get Ship TouchData( struct { float x, y, radius } )
	// TouchData :  mean = Circle Data For UnitSelect
	tagTouch getShipTouchData() const
	{
		return m_stUnitTouch;
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

	int getFleetNumber() const
	{
		return m_nFleetNumber;
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
};

#endif // !_BATTLE_UNIT_H