#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "systemBase.h"
#include "mapDataParser.h"
#include "mapObject.h"
#include "mapTile.h"
#include "mapEventObject.h"

namespace mapSystemNS
{
	const UINT MAP_SIZE_X = 128;
	const UINT MAP_SIZE_Y = 128;
	const UINT TILE_BASIC_WIDTH		= 128;
	const UINT TILE_BASIC_HEIGHT	= 64;

	const std::string BASIC_TILE_A = "A_isoBasicA";
	const std::string BASIC_TILE_B = "A_isoBasicB";
	const std::string BASIC_TILE_C = "A_isoBasicC";
}

enum class MAPTYPE
{
	DIAMOND,
	SQUARE,
	FREE,
	NONE,
};

class LogViewer;
class MapTileData;
class CameraSystem;
class MapSystem : public SystemBase
{
private:
	typedef std::vector<MapTile*>					MAP_TILES;
	typedef std::vector<MapTile*>::iterator			MAP_TILES_ITER;
	typedef std::vector<MapObject*>					MAP_OBJECTS;
	typedef std::vector<MapObject*>::iterator		MAP_OBJECTS_ITER;
	typedef std::vector<MapEventObject*>			MAP_EVENT_OBJECT;
	typedef std::vector<MapEventObject*>::iterator	MAP_EVENT_OBJECT_ITER;
private:
	MAP_TILES	m_arrTiles;					// Map Cells(TILE)
	MAP_OBJECTS m_arrObjects;				// Map Object
	MAP_EVENT_OBJECT m_arrEventObjects;		// Map EventObject
private:	// For UI Work Variables
	std::vector<RECT> m_arrWorkableRECT;
	MAPTYPE m_mapType;

private: // bool Variables For Debug
	bool m_bDebugTiles;
	bool m_bDebugObject;
	bool m_bDebugEventObject;
	bool m_bDebug;
private: // Map Tile & Object Data Pointer
	MapTileData* m_pMapTileData;		// MapData For Setup Tiles
	bool m_bMakeObject;	// Flag For Make Object (This Flag Not Meaning EventObject)
	bool m_bEventObjectMode;
private: // MapData Parser
	MapDataParser* m_pMapDataParser;	// MapData Parser For Save / Load

	// Forward Pointer
	CameraSystem* m_pCameraSystem;
	LogViewer* m_pLogViewer;
public:
	MapSystem();
	~MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ============================================
	// Member Functions
	// ============================================
	void moveX(int distance);
	void moveY(int distance);

	// All Tile Reset to Basic Tiles
	void resetMap()
	{
		resetTiles();
		resetObjects();
		resetEventObject();
	}

	// Reset All Tiles Texture Function
	void resetTiles()
	{
		for (auto iter : m_arrTiles)
		{
			iter->changeTexture(mapSystemNS::BASIC_TILE_C);
		}
	}

	// Reset Objects Function
	void resetObjects()
	{
		for (auto iter : m_arrObjects)
		{
			SAFE_DELETE(iter);
		}
		m_arrObjects.clear();
	}

	// Reset EventObjects Function
	void resetEventObject()
	{
		for (auto iter : m_arrEventObjects)
		{
			SAFE_DELETE(iter);
		}
		m_arrEventObjects.clear();
	}

	void changeClickedTile();
	void setOnTileObject();

	// Add Map Object Function
	void addObject(MapObject* pObject)
	{
		m_arrObjects.emplace_back(pObject);
	}
	// Add Map Event Object Function
	void addEventObject(MapEventObject* pEventObject)
	{
		m_arrEventObjects.emplace_back(pEventObject);
	}

	// Add UI Dialog Viewer RECT For Blocking Mouse Click on Dialog
	void addWorkRECT(RECT rc)
	{
		m_arrWorkableRECT.emplace_back(rc);
	}

	// All Tile Data Save Function
	void saveData();

	// All Tile Data Load Function
	void loadData();
	// ============================================
	// Setter Functions
	// ============================================

	// Set Make Event Object Mode Flag Function
	void setMakeEventObjectMode(bool b)
	{
		m_bEventObjectMode = b;
	}
	// Set Debug Mode On/Off
	void setDebug()
	{
		m_bDebug = !m_bDebug;
	}
	// Set Object Debug Mode On/Off
	void setDebugObject()
	{
		m_bDebugObject = !m_bDebugObject;
	}
	// Set Event Object Debug Mode On/Off
	void setDebugEventObject()
	{
		m_bDebugEventObject = !m_bDebugEventObject;
	}
	// Set Tile Debug Mode On/Off
	void setDebugTile()
	{
		m_bDebugTiles = !m_bDebugTiles;
	}
	// Set MapTileData (Forward Pointer)
	void setMapTileData(MapTileData* pMapTileData)
	{
		m_pMapTileData = pMapTileData;
	}
	// set Make Object Mode Flag Function
	void setMakeObjectMode(bool b)
	{
		m_bMakeObject = b;
	}

	// ============================================
	// Getter Functions
	// ============================================

	// get Debug Flag
	bool getDebug() const
	{
		return m_bDebug;
	}
	// get Debug Cell Flag
	bool getDebugTile() const
	{
		return m_bDebugTiles;
	}
	// get Debug Object Flag
	bool getDebugObject() const
	{
		return m_bDebugObject;
	}
	// get Debug Event Object Flag
	bool getDebugEventObject() const
	{
		return m_bDebugEventObject;
	}
	
	std::vector<MapTile*> getAllTiles() const
	{
		return m_arrTiles;
	}
	std::vector<MapObject*> getAllObjects() const
	{
		return m_arrObjects;
	}
	MapTile* getTile(int number);
	MapTile* getTile(int num) const
	{
		return m_arrTiles[num];
	}
	bool getMakeObjectMode() const
	{
		return m_bMakeObject;
	}

	// MemoryLink Functions
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem);
	void setMemoryLinkLogViewer(LogViewer* pLogViewer)
	{ m_pLogViewer = pLogViewer; }
};

#endif // !_MAPSYSTEM_H
