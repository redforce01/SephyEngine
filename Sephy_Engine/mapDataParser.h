#ifndef _MAPDATAPARSER_H
#define _MAPDATAPARSER_H

class MapDataParser;

#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include "mapSystem.h"
#include "mapTile.h"
#include "mapObject.h"
#include "mapEventObject.h"

namespace mapDataParserNS
{
	const std::string LOAD_FILE_NAME = "Resources\\20_MapData\\createdBattleMap.mdf";
	const std::string SAVE_FILE_NAME = "Resources\\20_MapData\\createdBattleMap.mdf";
	const std::string TAB_ONE = "\t";
	const std::string TAB_TWO = "\t\t";
	const std::string TAB_THREE = "\t\t\t";
	const std::string TAB_FOUR = "\t\t\t\t";
	const std::string DATA_REMARK = "#";
}

namespace mapDataMessageNS
{
	//=====================================================
	// Map Data List - Start
	const std::string VERSION = "Version";
	const std::string CELL_X = "NumCellsX";
	const std::string CELL_Y = "NumCellsY";
	const std::string ORIGIN_X = "OriginX";
	const std::string ORIGIN_Y = "OriginY";
	const std::string ORIGIN_W = "OriginW";
	const std::string ORIGIN_H = "OriginH";
	const std::string MADE_TIME = "MadeTime";
	const std::string RANDOM_SEED = "RandomSeed";
	const std::string OBJECT_SIZE = "ObjectSize";
	const std::string COLLISION_SIZE = "CollisionBoxSize";
	// Map Data List - End
	//=====================================================
	// Map Data DATA tag List & Key - Start
	const std::string DATA_START_KEY = "BEGIN";
	const std::string DATA_END_KEY = "END";
	const std::string CELL_START_MESSAGE = "Cells";
	const std::string OBJECT_START_MESSAGE = "Objects";
	const std::string EVENT_OBJECT_START_MESSAGE = "EventObject";
	const std::string COLLISION_START_MESSAGE = "CollisionBox";
	// Map Data DATA tag List & Key - End
	//=====================================================
}

struct tagMapDataInfo
{
	std::string Version;
	UINT CellsX;
	UINT CellsY;
	UINT OriginX;
	UINT OriginY;
	UINT Width;
	UINT Height;
	std::string MadeTime;
	UINT RandomSeed;
	UINT ObjectSize;
	UINT CollisionBoxSize;
};

class CameraSystem;
class MapSystem;
class MapDataParser
{
private:
	typedef std::vector<MapTile*> MAP_TILES;
	typedef std::vector<MapObject*> MAP_OBJECTS;
	typedef std::vector<MapEventObject*> MAP_EVENTOBJECTS;

private: // Real Map Data From MapSystem
	MAP_TILES m_arrMapTile;
	MAP_OBJECTS m_arrMapObject;
	MAP_EVENTOBJECTS m_arrMapEventObject;
private: // Member variables
	tagMapDataInfo m_MapDataInfo;
	std::vector<std::string> m_vData;

	std::thread m_LoadingThread;	// Save/Load Thread
	bool m_bLoading;				// For Thread Loading Flag ( true = loading... || false = Loading Complete)
	bool m_bCallFunction;			// 

	// MapSystem Pointer For forward Pointer
	MapSystem* m_pMapSystem;
	CameraSystem* m_pCameraSystem;
public:
	MapDataParser();
	~MapDataParser();

	// Set MapSystem Memory Link Function
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem)
	{ m_pCameraSystem = pCameraSystem; }
	// ===================================================
	// Member Functions
	// ===================================================
	void setMapDataInfo(tagMapDataInfo gInfo)
	{
		m_MapDataInfo = gInfo;
	}


	// Save Functions
	bool saveData();											// Save Function
	static void SaveThreadFunc();								// For Save Thread Functions
	
	// Load Functions
	bool loadData();											// Load Function
	void arrayRecognize(std::vector<std::string> vArray);
	void mapCellSetup(std::vector<std::string> vMapCells);
	void mapObjectSetup(std::vector<std::string> vObjectCells);
	void mapEventObjectSetup(std::vector<std::string> vEventObject);

	// std::vector<std::string> arraySeperation(char message[]);	// Array Seperator
	// bool recognizeData(std::vector<std::string> vArray);		// Recognize Array Function
	// bool mapSetup(std::vector<std::string> vData);				// Setup MapSystem MapTiles (using Recognized Data)
	static void LoadThreadFunc();								// For Load Thread Functions

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
	void setMapEventObject(std::vector<MapEventObject*> pMapEventObject)
	{
		m_arrMapEventObject = pMapEventObject;
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
