#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "systemBase.h"
#include "mapDataParser.h"
#include "mapTile.h"

namespace mapSystemNS
{
	const UINT mapSizeX = 128;
	const UINT mapSizeY = 128;
	const UINT tileBasicWidth = 128;
	const UINT tileBasicHeight = 64;

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
	typedef std::vector<MapTile*>			MAP_TILES;
	typedef std::vector<MapTile*>::iterator	MAP_TILES_ITER;
private:
	MAP_TILES m_arrTiles;
	std::vector<RECT> m_arrWorkableRECT;
	MAPTYPE m_mapType;
	bool m_bDebug;

	MapTileData* m_pMapTileData;
	MapDataParser* m_pMapDataParser;

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
	void scaleUp();
	void scaleDown();

	// All Tile Reset to Basic Tiles
	void resetMap()
	{
		for (auto iter : m_arrTiles)
		{
			iter->changeTexture(mapSystemNS::BASIC_TILE_A);
		}
	}

	void changeClickedTile();
	void changeClickedObject();

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
	void setDebug()
	{
		m_bDebug = !m_bDebug;
	}
	void setMapTileData(MapTileData* pMapTileData)
	{
		m_pMapTileData = pMapTileData;
	}

	// ============================================
	// Getter Functions
	// ============================================
	bool getDebug() const
	{
		return m_bDebug;
	}
	MapTile* getTile(int number);
	std::vector<MapTile*> getAllTiles() const
	{
		return m_arrTiles;
	}
	MapTile* getTile(int num) const
	{
		return m_arrTiles[num];
	}
	
	// MemoryLink Functions
	void setMemoryLinkCameraSystem(CameraSystem* pCamSys)
	{ m_pCameraSystem = pCamSys; }
	void setMemoryLinkLogViewer(LogViewer* pLogViewer)
	{ m_pLogViewer = pLogViewer; }
};

#endif // !_MAPSYSTEM_H
