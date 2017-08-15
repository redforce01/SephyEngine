#include "stdafx.h"
#include "Battle_TurretParser.h"


CBattle_TurretParser::CBattle_TurretParser()
{
}


CBattle_TurretParser::~CBattle_TurretParser()
{
}

std::vector<std::string> CBattle_TurretParser::loadTurretData(std::string turretName)
{
	auto vData = TXTDATA_PARSER->loadDataToArray(turretName);
	return recogTurretData(vData);
}

std::vector<std::string> CBattle_TurretParser::recogTurretData(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return std::vector<std::string>();

	std::vector<std::string> vData;

	for (auto iter : vArray)
	{
		if (iter.compare(TurretParserNS::DATA_BEGIN_KEY + " " + TurretParserNS::SHIP_DATA_KEY) == false)
			continue;
		else if (iter.compare(TurretParserNS::SHIP_DATA_KEY + " " + TurretParserNS::DATA_END_KEY) == false)
			continue;

		vData.emplace_back(iter);
	}

	return setupTurretData(vData);
}

std::vector<std::string> CBattle_TurretParser::setupTurretData(std::vector<std::string> vArray)
{
	int dataNumber = 0;
	std::vector<std::string> vResult;

	vResult.emplace_back(vArray[dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret ID
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret Name
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//   #  + Turret RotatedSpeed
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret FireRate
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Barrel Count
	//====================================================================================
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet Speed
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet Damage
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet TextureKey_Hit
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet TextureKey_Miss
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet TextureKey_Hit_MaxFrame
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Bullet TextureKey_Miss_MaxFrame
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Miss Sound File Name
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));	//	 #  + Turret Fire Sound File Name

	return vResult;
}
