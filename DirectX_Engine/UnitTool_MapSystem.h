#ifndef _UNITTOOL_MAPSYSTEM_H
#define _UNITTOOL_MAPSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_MapSystem;

#include "systemBase.h"
#include "mapTile.h"

namespace unitToolMapSystemNS
{
	const std::string BASIC_TILE_C = "A_isoBasicC";
	const UINT MAP_CELL_X = 64;
	const UINT MAP_CELL_Y = 128;
	const UINT MAP_CELL_WIDTH = 128;
	const UINT MAP_CELL_HEIGHT = 64;
}

class CUnitTool_MapSystem : public SystemBase
{
private:
	std::vector<MapTile*> m_vMapCells;
	

public:
	CUnitTool_MapSystem();
	~CUnitTool_MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_UNITTOOL_MAPSYSTEM_H
