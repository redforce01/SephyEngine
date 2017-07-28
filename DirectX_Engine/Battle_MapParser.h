#ifndef _BATTLE_MAPPARSER_H
#define _BATTLE_MAPPARSER_H

class CBattle_MapParser;

#include <string>
#include <fstream>
#include <sstream>
#include "mapTile.h"
#include "mapObject.h"
#include "mapEventObject.h"

namespace battleMapParserNS
{
	const std::string ERROR_MESSAGE = "Battle Map Data Parsing Failed";
	const std::string MAPDATA_FOLDER_NAME = "33_BattleMapData";
}

namespace battleMapDataMessageNS
{
	//=====================================================
	// Map Data Tabs
	const std::string TAB_ONE = "\t";
	const std::string TAB_TWO = "\t\t";
	const std::string TAB_THREE = "\t\t\t";
	const std::string TAB_FOUR = "\t\t\t\t";
	const std::string DATA_REMARK = "#";
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
	const float ISOMETRIC_HEIGHT_TOTAL_RATE = 0.5f;
	
}

struct tagMapBattleDataInfo
{
	std::string Version;
	UINT CellsX;
	UINT CellsY;
	UINT OriginX;
	UINT OriginY;
	UINT OriginWidth;
	UINT OriginHeight;
	std::string MadeTime;
	UINT RandomSeed;
	UINT ObjectSize;
	UINT CollisionBoxSize;
};

class CBattle_CameraSystem;
class CBattle_MapSystem;
class CBattle_MapParser
{
private:
	std::vector<MapTile*>			m_loadedCells;
	std::vector<MapObject*>			m_loadedObjects;
	std::vector<MapEventObject*>	m_loadedEventObjects;
private:
	std::string				m_strLoadFileName;	// Load File Name
	tagMapBattleDataInfo	m_MapDataInfo;		// Map Data General Informations
	Graphics*				m_pGraphics;		// Graphics Pointer For - Battle Map Tile(Cell) Setup

private: // Forward Pointer Variables
	CBattle_MapSystem*		m_pBattleMapSystem;
	CBattle_CameraSystem*	m_pBattleCameraSystem;
public:
	CBattle_MapParser();
	~CBattle_MapParser();

	// Load Battle Map Data Function
	bool loadBattleMapData(std::string mapFileName);

	void setGraphics(Graphics* pGraphics)
	{
		m_pGraphics = pGraphics;
	}

	// BattleMap System Forward Pointer MemoryLink Function
	void setMemoryLinkBattleMapSystem(CBattle_MapSystem* pBattleMapSystem)
	{
		m_pBattleMapSystem = pBattleMapSystem;
	}
	void setMemoryLinkBattleCameraSystem(CBattle_CameraSystem* pBattleCameraSystem)
	{
		m_pBattleCameraSystem = pBattleCameraSystem;
	}

private: // Load Memeber Function
	void mapDataRecognize(std::vector<std::string> vArray);

	void loadBattleMapCells(std::vector<std::string> vMapCells);
	void loadBattleMapObjects(std::vector<std::string> vMapObjects);
	void loadBattleMapEventObjects(std::vector<std::string> vMapEventObjects);

public:
	tagMapBattleDataInfo getMapDataInfo() const
	{
		return m_MapDataInfo;
	}
	std::vector<MapTile*> getLoadedCells() const
	{
		return m_loadedCells;
	}
	std::vector<MapObject*> getLoadedObjects() const
	{
		return m_loadedObjects;
	}
	std::vector<MapEventObject*> getLoadedEventObjects() const
	{
		return m_loadedEventObjects;
	}
};

#endif // !_BATTLE_MAPPARSER_H
