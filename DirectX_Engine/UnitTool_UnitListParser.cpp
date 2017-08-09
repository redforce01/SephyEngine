#include "stdafx.h"
#include "UnitTool_UnitListParser.h"


CUnitTool_UnitListParser::CUnitTool_UnitListParser()
{
}


CUnitTool_UnitListParser::~CUnitTool_UnitListParser()
{
}

std::vector<std::string> CUnitTool_UnitListParser::loadShipList()
{
	auto vData = TXTDATA_PARSER->loadDataToArray(unitToolUnitListDataParserNS::SHIPLIST_DATA_FILENAME);
	if (vData.size() > 0)
		return vData;
}

std::vector<std::string> CUnitTool_UnitListParser::loadUnitList()
{
	auto vData = TXTDATA_PARSER->loadDataToArray(unitToolUnitListDataParserNS::UNITLIST_DATA_FILENAME);
	if (vData.size() > 0)
		return vData;
}
