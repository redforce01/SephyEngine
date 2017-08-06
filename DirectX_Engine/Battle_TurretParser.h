#ifndef _BATTLE_TURRET_PARSER_H
#define _BATTLE_TURRET_PARSER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_TurretParser;


namespace TurretParserNS
{
	const std::string DATA_BEGIN_KEY = "BEGIN";
	const std::string DATA_END_KEY = "END";
	const std::string SHIP_DATA_KEY = "TurretData";
}

namespace battleTurretParserNS
{
	// Not Using namespace...
}


class CBattle_TurretParser
{
public:
	CBattle_TurretParser();
	~CBattle_TurretParser();

	//================================================
	// Load Turret Data Parser - Function
	//  + This Function Working for Only ShipData File
	//  + Parameter : std::string fileName
	//  + Result : std::vector<std::string>
	//================================================
	std::vector<std::string> loadTurretData(std::string turretName);

private:
	std::vector<std::string> recogTurretData(std::vector<std::string> vArray);
	std::vector<std::string> setupTurretData(std::vector<std::string> vArray);
};

#endif // !_BATTLE_TURRET_PARSER_H
