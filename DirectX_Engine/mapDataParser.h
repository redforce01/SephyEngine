#ifndef _MAPDATAPARSER_H
#define _MAPDATAPARSER_H

class MapDataParser;

#include <thread>
#include "mapSystem.h"
#include "mapTile.h"
#include "mapObject.h"

namespace mapDataParserNS
{
	const std::string LOAD_FILE_NAME = "battleMap.txt";
	const std::string SAVE_FILE_NAME = "battleMap.txt";
	const std::string MAP_TILE_IP = "MAP TILE NAME : ";
	const std::string MAP_OBJECT_IP = "MAP OBJECT NAME : ";	
}

class MapSystem;
class MapDataParser
{
private:
	typedef std::vector<MapTile*> MAP_TILES;
	typedef std::vector<MapObject*> MAP_OBJECTS;

private:
	MAP_TILES m_arrMapTile;
	MAP_OBJECTS m_arrMapObject;

	bool m_bLoading;
	bool m_bCallFunction;

	// MapSystem Pointer For forward Pointer
	MapSystem* m_pMapSystem;
public:
	MapDataParser();
	~MapDataParser();
	// ===================================================
	// Member Functions
	// ===================================================
	void recognizeData(std::vector<std::string> vArray);

	// Save Functions
	void saveData();											// Save Function
	std::string arrayCombine(std::vector<std::string> vArray);	// Array Combine Function
	static void SaveThreadFunc();								// For Save Thread Functions
	
	// Load Functions
	std::vector<std::string> loadData();						// Load Function
	static void LoadThreadFunc();								// For Load Thread Functions
	std::vector<std::string> arraySeperation(char message[]);	// Array Seperator


	// ===================================================
	// Setter Functions
	// ===================================================
	void setMapTiles(std::vector<MapTile*> pArrMapTile)
	{
		m_arrMapTile = pArrMapTile;
	}
	void setMapObjects(std::vector<MapObject*> pMapObject)
	{
		m_arrMapObject = pMapObject;
	}

	// ===================================================
	// Getter Functions
	// ===================================================
	MAP_TILES getMapTiles() const
	{
		return m_arrMapTile;
	}
	MAP_OBJECTS getMapObjects() const
	{
		return m_arrMapObject;
	}

};

#endif // !_MAPDATAPARSER_H
