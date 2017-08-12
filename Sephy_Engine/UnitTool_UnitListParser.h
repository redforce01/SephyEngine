#ifndef _UNITTOOL_UNITLIST_PARSER_H
#define _UNITTOOL_UNITLIST_PARSER_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_UnitListParser;

namespace unitToolUnitListDataParserNS
{
	const std::string SHIPLIST_DATA_FILENAME = "UnitTool_ShipListData";
	const std::string UNITLIST_DATA_FILENAME = "UnitTool_UnitListData";
}

class CUnitTool_UnitListParser
{
public:
	CUnitTool_UnitListParser();
	~CUnitTool_UnitListParser();

	std::vector<std::string> loadShipList();
	std::vector<std::string> loadUnitList();

};

#endif // !_UNITTOOL_UNITLIST_PARSER_H
