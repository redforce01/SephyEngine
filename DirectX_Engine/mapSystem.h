#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "tileObject.h"
#include "systemBase.h"

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
	std::vector<TileObject*> arrTiles;
	MAPTYPE mapType;

	CameraSystem* m_pCameraSystem;
	MapTileData* m_pMapTileData;
public:
	MapSystem();
	~MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void moveX(int distance);
	void moveY(int distance);
	void scaleUp();
	void scaleDown();

	std::vector<TileObject*> getAllTiles() { return arrTiles; }
	TileObject* selectTile(int number);

	void setMapTileData(MapTileData* pMapTileData)
	{
		m_pMapTileData = pMapTileData;
	}

	void setMemoryLinkCameraSystem(CameraSystem* pCamSys) { m_pCameraSystem = pCamSys; }
};

#endif // !_MAPSYSTEM_H
