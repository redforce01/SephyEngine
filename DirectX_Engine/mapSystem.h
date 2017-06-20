#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "tileObject.h"

namespace MapSystemNS
{
	const UINT mapSizeX = 64;
	const UINT mapSizeY = 64;
	const UINT tileBasicWidth = 128;
	const UINT tileBasicHeight = 128;
}

enum class MAPTYPE
{
	DIAMOND,
	SQUARE,
	FREE,
	NONE,
};

class CameraSystem;
class MapSystem
{
private:
	std::vector<TileObject*> arrTiles;
	MAPTYPE mapType;

	CameraSystem* pCameraSystem;
public:
	MapSystem();
	~MapSystem();

	bool initialize(Game* gamePtr);
	void update(float frameTime);
	void render();

	void moveX(float distance);
	void moveY(float distance);
	void scaleUp();
	void scaleDown();


	std::vector<TileObject*> getAllTiles() { return arrTiles; }

	TileObject* selectTile(int number);
	void setMemoryLinkCameraSystem(CameraSystem* pCamSys) { pCameraSystem = pCamSys; }
};

#endif // !_MAPSYSTEM_H
