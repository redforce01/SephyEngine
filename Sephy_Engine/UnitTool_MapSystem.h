#ifndef _UNITTOOL_MAPSYSTEM_H
#define _UNITTOOL_MAPSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_MapSystem;

#include "systemBase.h"
#include "mapTile.h"

namespace unitToolMapSystemNS
{
	const std::string BASIC_TILE_C = "A_isoBasicC";
	const UINT MAP_CELL_X = 128;
	const UINT MAP_CELL_Y = 196;
	const UINT MAP_CELL_WIDTH = 128;
	const UINT MAP_CELL_HEIGHT = 64;
	const float ISOMETRIC_HEIGHT_TOTAL_RATE = 0.3f;
}

class CUnitTool_MapSystem : public SystemBase
{
private:
	std::vector<MapTile*> m_vMapCells;	

private: // width, height Variables For Battle_CameraSystem [For Camera Min Max Position Setup]
	float m_fMapTotalWidth;
	float m_fMapTotalHeight;
	float m_fMapCellWidth;
	float m_fMapCellHeight;

public:
	CUnitTool_MapSystem();
	~CUnitTool_MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//=============================================
	// Member Functions
	//=============================================
	void moveX(int distance);	// Move X [Tile]
	void moveY(int distance);	// Move Y [Tile]


	//=============================================
	// Setter Functions
	//=============================================

	void setMapTotalWidth(float fWidth)
	{
		m_fMapTotalWidth = fWidth;
	}
	void setMapTotalHeight(float fHeight)
	{
		m_fMapTotalHeight = fHeight;
	}
	void setCellWidth(float fWidth)
	{
		m_fMapCellWidth = fWidth;
	}
	void setCellHeight(float fHeight)
	{
		m_fMapCellHeight = fHeight;
	}

	//=============================================
	// Getter Functions
	//=============================================

	float getMapTotalWidth() const
	{
		return m_fMapTotalWidth;
	}
	float getMapTotalHeight() const
	{
		return m_fMapTotalHeight;
	}
	float getCellWidth() const
	{
		return m_fMapCellWidth;
	}
	float getCellHeight() const
	{
		return m_fMapCellHeight;
	}
};

#endif // !_UNITTOOL_MAPSYSTEM_H
