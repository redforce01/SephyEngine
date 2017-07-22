#ifndef _MAPOBJECT_PARSER_H
#define _MAPOBJECT_PARSER_H

class MapObjectParser;

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "mapTileData.h"

namespace mapObjectParserNS
{
	const std::string DATA_FILE_NAME = "BattleMap Object Data";
}

class MapObjectParser
{
public:
	MapObjectParser();
	~MapObjectParser();

	std::vector<std::string> loadObjectData();

	void recogData(std::vector<std::string> vData);

	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
};

#endif // !_MAPOBJECT_PARSER_H
