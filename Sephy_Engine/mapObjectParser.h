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
	typedef std::vector<MapTileData*> VIEWER_ITEMS;
private:
	VIEWER_ITEMS m_vTileList;
	VIEWER_ITEMS m_vObjectList;

public:
	MapObjectParser();
	~MapObjectParser();

	// ===================================================
	// Member Functions
	// ===================================================

	std::vector<std::string> loadObjectData();
	void recogData(std::vector<std::string> vData);
	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);

	// ===================================================
	// Getter Functions
	// ===================================================
	std::vector<MapTileData*> getTileList() const
	{
		return m_vTileList;
	}
	std::vector<MapTileData*> getObjectList() const
	{
		return m_vObjectList;
	}
	
};

#endif // !_MAPOBJECT_PARSER_H
