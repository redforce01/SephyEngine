#include "stdafx.h"
#include "Battle_UnitParser.h"
#include "Battle_UnitSystem.h"

CBattle_UnitParser::CBattle_UnitParser()
{
}


CBattle_UnitParser::~CBattle_UnitParser()
{
}

std::vector<std::string> CBattle_UnitParser::loadShipData(std::string shipName)
{
	auto vData = TXTDATA_PARSER->loadDataToArray(shipName);
	return recogShipData(vData);
}

std::vector<std::string> CBattle_UnitParser::recogShipData(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return std::vector<std::string>();

	std::vector<std::string> vData;

	for (auto iter : vArray)
	{
		if (iter.compare(UnitParserNS::DATA_BEGIN_KEY + " " + UnitParserNS::SHIP_DATA_KEY) == false)
			continue;
		else if (iter.compare(UnitParserNS::SHIP_DATA_KEY + " " + UnitParserNS::DATA_END_KEY) == false)
			continue;

		vData.emplace_back(iter);
	}

	return setupShipData(vData);
}

std::vector<std::string> CBattle_UnitParser::setupShipData(std::vector<std::string> vArray)
{
	int dataNumber = 0;
	std::vector<std::string> vResult;

	vResult.emplace_back(vArray[dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));
	vResult.emplace_back(vArray[++dataNumber].substr(vArray[dataNumber].rfind('\t') + 1));

	return vResult;
}
