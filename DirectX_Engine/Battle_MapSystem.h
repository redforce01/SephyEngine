#ifndef _BATTLE_MAPSYSTEM_H
#define _BATTLE_MAPSYSTEM_H

class CBattle_MapSystem;

#include "systemBase.h"
#include "mapTile.h"
#include "mapObject.h"
#include "mapEventObject.h"
#include "Battle_MapParser.h"

namespace battleMapSystemNS
{
	const std::string ERROR_MESSAGE = "Battle MapData Initialize Failed";
	const std::string BASIC_TILE_A = "A_isoBasicA";
	const std::string BASIC_TILE_B = "A_isoBasicB";
	const std::string BASIC_TILE_C = "A_isoBasicC";
}

class CBattle_CameraSystem;
class CBattle_MapSystem : public SystemBase
{
private:
	typedef std::vector<MapTile*>					MAP_TILES;
	typedef std::vector<MapTile*>::iterator			MAP_TILES_ITER;
	typedef std::vector<MapObject*>					MAP_OBJECTS;
	typedef std::vector<MapObject*>::iterator		MAP_OBJECTS_ITER;
	typedef std::vector<MapEventObject*>			MAP_EVENT_OBJECT;
	typedef std::vector<MapEventObject*>::iterator	MAP_EVENT_OBJECT_ITER;

private:
	std::string			m_strMapName;
	MAP_TILES			m_vCells;
	MAP_OBJECTS			m_vObjects;
	MAP_EVENT_OBJECT	m_vEventObjects;

private: // width/height Variables For Battle_CameraSystem [For Camera Min Max Position Setup]
	float m_fMapTotalWidth;
	float m_fMapTotalHeight;
	float m_fMapCellWidth;
	float m_fMapCellHeight;

private: // Battle MapParser
	CBattle_MapParser* m_pBattleMapDataParser;

public:
	CBattle_MapSystem();
	~CBattle_MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//=============================================
	// Member Functions
	//=============================================
	void moveX(int distance);	// Move X [Tile, Object, Event Object]
	void moveY(int distance);	// Move Y [Tile, Object, Event Object]

	// ============================================
	// Load Battle Map File Information
	//  + if read Null FileData ? return false
	//  + Using FILEMANAGER SYSTEM
	//  + read from all Resources folders .find(mapName)
	// ============================================
	bool loadBattleMap(std::string mapName);

	// Forward Pointer Functions
	void setMemoryLinkBattleCameraSystem(CBattle_CameraSystem* pBattleCameraSystem)
	{
		m_pBattleMapDataParser->setMemoryLinkBattleCameraSystem(pBattleCameraSystem);
	}
	//=============================================
	// Reset Functions
	//=============================================
	// Reset All Tiles Texture Function
	void resetTiles()
	{
		for (auto iter : m_vCells)
		{
			iter->changeTexture(battleMapSystemNS::BASIC_TILE_C);
		}
	}
	// Reset Objects Function
	void resetObjects()
	{
		for (auto iter : m_vObjects)
		{
			SAFE_DELETE(iter);
		}
		m_vObjects.clear();
	}
	// Reset EventObjects Function
	void resetEventObject()
	{
		for (auto iter : m_vEventObjects)
		{
			SAFE_DELETE(iter);
		}
		m_vEventObjects.clear();
	}	

	//=============================================
	// Add Object/Event Object Functions
	//=============================================

	// Add Map Object Function
	void addObject(MapObject* pObject)
	{
		m_vObjects.emplace_back(pObject);
	}
	// Add Map Event Object Function
	void addEventObject(MapEventObject* pEventObject)
	{
		m_vEventObjects.emplace_back(pEventObject);
	}

	//=============================================
	// Setter Functions
	//=============================================

	void setAllTiles(std::vector<MapTile*> pArrCells)
	{
		m_vCells = pArrCells;
	}
	void setAllObject(std::vector<MapObject*> pArrObjects)
	{
		m_vObjects = pArrObjects;
	}
	void setAllEventObject(std::vector<MapEventObject*> pArrEventObjects)
	{
		m_vEventObjects = pArrEventObjects;
	}
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
	
	std::vector<MapTile*> getAllTiles() const
	{
		return m_vCells;
	}
	std::vector<MapObject*> getAllObjects() const
	{
		return m_vObjects;
	}
	std::vector<MapEventObject*> getAllEventObject() const
	{
		return m_vEventObjects;
	}
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

#endif // !_BATTLE_MAPSYSTEM_H
