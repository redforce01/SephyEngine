#ifndef _MAPSYSTEM_H
#define _MAPSYSTEM_H

class MapSystem;

#include <vector>
#include <memory>
#include "tileObject.h"
#include "systemBase.h"

namespace MapSystemNS
{
	const UINT mapSizeX = 64;
	const UINT mapSizeY = 64;
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

class CameraSystem;
class MapSystem : public SystemBase
{
private:
	std::vector<TileObject*> arrTiles;
	MAPTYPE mapType;

	CameraSystem* pCameraSystem;
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
	void setMemoryLinkCameraSystem(CameraSystem* pCamSys) { pCameraSystem = pCamSys; }
};

#endif // !_MAPSYSTEM_H
