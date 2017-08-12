#ifndef _BATTLE_UNIT_PARSER_H
#define _BATTLE_UNIT_PARSER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UnitParser;

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace UnitParserNS
{
	const std::string DATA_BEGIN_KEY	= "BEGIN";
	const std::string DATA_END_KEY		= "END";
	const std::string SHIP_DATA_KEY		= "ShipData";
}

namespace battleUnitParserShipNS
{
	const std::string ID_KEY					= "ShipID";
	const std::string TEXTURE_KEY				= "TextureKey";
	const std::string TEXTURE_TOP_COUNT_KEY		= "TextureTop";
	const std::string TEXTURE_BODY_COUNT_KEY	= "TextureBody";
	const std::string TEXTURE_BOTTOM_COUNT_KEY	= "TextureBottom";
	const std::string NAME_KEY					= "Ship_Name";
	const std::string TYPE_KEY					= "Ship_Type";
	const std::string DP_KEY					= "DP";
	const std::string REPAIR_SPEED_KEY			= "Repair_Speed";
	const std::string ROTATE_SPEED_KEY			= "Rotate_Speed";
	const std::string ACCELERATE_SPEED_KEY		= "Accelerate_Speed";
	const std::string MAX_SPEED_KEY				= "Max_Speed";
	const std::string RADER_KEY					= "Rader";
	const std::string TURRET_CAPACITY_KEY		= "Turret_Capacity";
	const std::string TURRET_ID					= "Turret_ID";
	const std::string AIRCRAFT_CAPACITY_KEY		= "Aircraft_Capacity";
	const std::string PERFORMANCE_KEY			= "Performance";
	const std::string SAILOR_KEY				= "Sailor";
	const std::string ANTIAIR_CAPACITY_KEY		= "AntiAir_Capacity";
	const std::string ANTIAIR_RANGE_KEY			= "AntiAir_Range";
	const std::string ANTIAIR_DAMAGE_KEY		= "AntiAir_Damage";
	const std::string SKILL_KEY					= "Skill";
}

class CBattle_UnitParser
{
public:
	CBattle_UnitParser();
	~CBattle_UnitParser();

	//================================================
	// Load Ship Data Parser - Function
	//  + This Function Working for Only ShipData File
	//  + Parameter : std::string fileName
	//  + Result : std::vector<std::string>
	//================================================
	std::vector<std::string> loadShipData(std::string shipName);

private:
	std::vector<std::string> recogShipData(std::vector<std::string> vArray);
	std::vector<std::string> setupShipData(std::vector<std::string> vArray);
};																			

#endif // !_BATTLE_UNIT_PARSER_H


//================================================
// This Under Code Will be used For SaveShipData Function
// Those code Not used Current
//================================================
//std::string ID_KEY;
//std::string TEXTURE_KEY;
//std::string NAME_KEY;
//std::string TYPE_KEY;
//std::string DP_KEY;
//std::string REPAIR_SPEED_KEY;
//std::string ROTATE_SPEED_KEY;
//std::string ACCELERATE_SPEED_KEY;
//std::string MAX_SPEED_KEY;
//std::string RADER_KEY;
//std::string TURRET_CAPACITY_KEY;
//std::string TURRET_ID;
//std::string AIRCRAFT_CAPACITY_KEY;
//std::string PERFORMANCE_KEY;
//std::string SAILOR_KEY;
//std::string ANTIAIR_CAPACITY_KEY;
//std::string ANTIAIR_RANGE_KEY;
//std::string ANTIAIR_DAMAGE_KEY;
//std::string SKILL_KEY;