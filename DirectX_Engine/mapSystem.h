#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "mapTile.h"
#include "systemBase.h"
#include "mapDataParser.h"

namespace MapSystemNS
{
	const UINT mapSizeX = 128;
	const UINT mapSizeY = 128;
	const UINT tileBasicWidth = 128;
	const UINT tileBasicHeight = 64;
}

enum class MAPTYPE
{
	DIAMOND,
	SQUARE,
	FREE,
	NONE,
};

class MapTileData;
class CameraSystem;
class MapSystem : public SystemBase
{
private:
	std::vector<MapTile*> m_arrTiles;
	std::vector<RECT> m_arrWorkableRECT;
	MAPTYPE m_mapType;
	bool m_bDebug;

	CameraSystem* m_pCameraSystem;
	MapTileData* m_pMapTileData;
	MapDataParser* m_pMapDataParser;
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
	
	void addWorkRECT(RECT rc)
	{
		m_arrWorkableRECT.emplace_back(rc);
	}
	MapTile* selectTile(int number);

	void saveData();
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
	std::vector<MapTile*> getAllTiles()
	{
		return m_arrTiles;
	}
	
	// MemoryLink Functions
	void setMemoryLinkCameraSystem(CameraSystem* pCamSys)
	{ m_pCameraSystem = pCamSys; }
};

#endif // !_MAPSYSTEM_H
