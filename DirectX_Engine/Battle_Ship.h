#ifndef _BATTLE_SHIP_H
#define _BATTLE_SHIP_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Ship;

#include <vector>
#include <string>
#include "Battle_UnitParser.h"

#include "entity.h"
#include "Battle_Turret.h"

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
	int m_nSpriteTopStart;					// Unit Top Sprite Start Number
	int m_nSpriteBodyStart;					// Unit Body Sprite Start Number
	int m_nSpriteBottomStart;				// Unit Bottom Sprite Start Number
	int m_nSpriteShadowStart;				// Unit Shadow Sprite Start Number
	int m_nSpriteWaveStart;					// Unit Wave Sprite Start Number
	int m_nSpriteSunkenStart;				// Unit Sunken Sprite Start Number
	int m_nSpriteSunkenShadowStart;			// Unit SunkenShadow Sprite Start Number
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
	struct tagTouch
	{
		float x, y;
		float radius;
	};
private:
	tagTouch m_stUnitTouch;	// For Unit Clicekd TouchData


private:
	CBattle_UnitParser m_UnitDataParser; // UNIT DATA PARSER

private:
	bool m_bInitialized;
	bool m_bActive;
	bool m_bDestroy; // Unit Destroyed Flag
	bool m_bDestroyAnimeComplete;
	bool m_bChangeSprite;
	bool m_bSelected;
	bool m_bOnEngine;
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
	}

	void setUnitSelected(bool bSelected)
	{
		m_bSelected = bSelected;
	}

	//===============================================
	// Getter Functions
	//===============================================

	bool getUnitSelected() const
	{
		return m_bSelected;
	}

	// Get Ship TouchData( struct { float x, y, radius } )
	tagTouch getShipTouchData() const
	{
		return m_stUnitTouch;
	}

	// Get Ship Entities
	std::vector<std::pair<bool, Entity*>> getShipParts() const
	{
		return m_vEntity;
	}
private:
	void setupShipDataFormat(std::vector<std::string> vArray);
	bool setupEntity(Game* gamePtr, std::string strImageName, bool bPhysics);
};

#endif // !_BATTLE_UNIT_H