#include "stdafx.h"
#include "mapSystem.h"
#include "CameraSystem.h"
#include "mapTileData.h"
#include "logViewer.h"

MapSystem::MapSystem()
{
	m_mapType = MAPTYPE::DIAMOND;
	m_pMapTileData = nullptr;
	m_pCameraSystem = nullptr;
	m_pMapDataParser = nullptr;
	m_pLogViewer = nullptr;

	m_bDebug = true;
	m_bDebugTiles = true;
	m_bDebugObject = true;
	m_bDebugEventObject = true;

	m_bMakeObject = false;
	m_bEventObjectMode = false;
}


MapSystem::~MapSystem()
{
	for (auto iter : m_arrTiles)
	{
		SAFE_DELETE(iter);
	}
	m_arrTiles.clear();

	for (auto iter : m_arrObjects)
	{
		SAFE_DELETE(iter);
	}
	m_arrObjects.clear();

	for (auto iter : m_arrEventObjects)
	{
		SAFE_DELETE(iter);
	}
	m_arrEventObjects.clear();

	SAFE_DELETE(m_pMapDataParser);
}

bool MapSystem::initialize(Game* gamePtr)
{
	bool success = false;

	m_pMapDataParser = new MapDataParser;
	m_pMapDataParser->setMemoryLinkMapSystem(this);

	int UIDCount = 0;
	int mapX, mapY;
	mapX = mapY = 0;

	if (gamePtr == nullptr)
		return false;

	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();

	// ==========================================================
	// Tile Map Initialize - Start
	// MapSystemNS::MAP_SIZE_X (basic = 128)
	// MapSystemNS::MAP_SIZE_Y (basic = 128)
	// for(row) {
	//	for(cols)
	//		{ m_arrTiles.emplace( new Tiles); }
	// }
	for (UINT row = 0; row < mapSystemNS::MAP_SIZE_X; row++)
	{
		for (UINT col = 0; col < mapSystemNS::MAP_SIZE_Y; col++)
		{
			MapTile* temp = new MapTile;
			temp->initialize(gamePtr->getGraphics(), UIDCount, mapSystemNS::BASIC_TILE_C,
				mapX, mapY, mapSystemNS::TILE_BASIC_WIDTH, mapSystemNS::TILE_BASIC_HEIGHT);
			m_arrTiles.emplace_back(temp);
			
			mapX += mapSystemNS::TILE_BASIC_WIDTH;
			UIDCount++;
		}
		mapY += mapSystemNS::TILE_BASIC_HEIGHT / 2;
		
		if (row % 2)
			mapX = 0;
		else mapX = mapSystemNS::TILE_BASIC_WIDTH / 2;
	}
	// Tile Map Initialize - End
	// ==========================================================
	
	return success;
}

void MapSystem::update(float frameTime)
{
	// Update All Tiles
	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All Objects
	for (auto iter : m_arrObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All EventObject
	for (auto iter : m_arrEventObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}


	if (m_bEventObjectMode)
		return;

	if (m_pInput->getMouseLButton())
	{
		for (auto iter : m_arrWorkableRECT)
		{
			if (PtInRect(&iter, m_pInput->getMousePt()))
			{
				if (m_bMakeObject)
				{
					m_pMapTileData->reset();
					m_bMakeObject = false;
				}

				return;
			}
		}
		
		if(m_bMakeObject == false)	// Set ChangeTile (On Tile)
			changeClickedTile();
		else
		{
			setOnTileObject();		// Set Object (Free Position || None FreePosition )
			m_pInput->setMouseLButton(false);
		}

	}
	
	if (m_pInput->isKeyDown(VK_DELETE))
	{
		if (m_bDebugObject)
		{
			for (auto iter = m_arrObjects.begin(); iter != m_arrObjects.end(); )
			{
				RECT rc = (*iter)->getObjectRect();
				POINT pt = m_pInput->getMousePt();
				if (PtInRect(&rc, pt))
				{
					SAFE_DELETE(*iter);
					m_arrObjects.erase(iter);
				}
				else
					iter++;
			}

		}

		if (m_bDebugEventObject)
		{
			for (auto iter = m_arrEventObjects.begin(); iter != m_arrEventObjects.end(); )
			{
				RECT rc = (*iter)->getEventObjectRECT();
				POINT pt = m_pInput->getMousePt();
				if (PtInRect(&rc, pt))
				{
					SAFE_DELETE(*iter);
					m_arrEventObjects.erase(iter);
				}
				else
					iter++;
			}
		}
	}

	// Update m_pMapTileData Set to Mouse Cursor PositionX,Y
	if (m_bMakeObject)
	{
		if(m_pMapTileData)
			m_pMapTileData->setPosition(m_pInput->getMouseX(), m_pInput->getMouseY());
	}


}

void MapSystem::render()
{
	m_pGraphics->spriteBegin();

	// Draw All Tiles
	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;
		
		iter->render();
	}

	// Draw All Objects
	for (auto iter : m_arrObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}

	for (auto iter : m_arrEventObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;
				
		iter->render();
	}

	if (m_bMakeObject)
	{
		if (m_pMapTileData == nullptr)
			return;

		if (m_pMapTileData->getTextureName() == "")
			return;

		m_pMapTileData->draw();
	}

	m_pGraphics->spriteEnd();

	// if Debug Mode On. Call RenderSketch()
	// This Function Will Drawing Each Object(include Tile)'s border Line
	if (m_bDebug)
	{
		if (m_bDebugTiles)
		{
			for (auto iter : m_arrTiles)
			{
				if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
					continue;

				iter->renderSketch();
			}
		}

		if (m_bDebugObject)
		{
			for (auto iter : m_arrObjects)
			{
				if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
					continue;

				iter->renderSketch();
			}
		}

		if (m_bDebugEventObject)
		{
			for (auto iter : m_arrEventObjects)
			{
				if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
					continue;

				iter->renderSketch();
			}
		}
	}
}

void MapSystem::moveX(int distance)
{
	for (auto iter : m_arrTiles)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}

	for (auto iter : m_arrObjects)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}
	for (auto iter : m_arrEventObjects)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}
}

void MapSystem::moveY(int distance)
{
	for (auto iter : m_arrTiles)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}

	for (auto iter : m_arrObjects)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}
	for (auto iter : m_arrEventObjects)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}
}

void MapSystem::changeClickedTile()
{
	if (m_pMapTileData == nullptr)
		return;

	std::string name;
	int count = 0;
	name = m_pMapTileData->getTextureName();
	for (auto iter : m_arrTiles)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
		{
			count++;
			continue;
		}

		if (MyUtil::getIsometricIn(iter->getTileRect(), m_pInput->getMousePt()))
		{
			if (iter->changeTexture(name))
			{
				std::string log;
				log = "Tile[" + std::to_string(count) + "] Texture Changed : " + name;
				m_pLogViewer->addLog(log);
			}
		}

		count++;
	}
}

void MapSystem::setOnTileObject()
{
	if (m_pMapTileData == nullptr)
		return;

	if (m_pMapTileData->getFreePosition() == false)
	{
		std::string name;
		int count = 0;
		name = m_pMapTileData->getTextureName();
		for (auto iter : m_arrTiles)
		{
			if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			{
				count++;
				continue;
			}

			if (MyUtil::getIsometricIn(iter->getTileRect(), m_pInput->getMousePt()))
			{
				MapObject* newObject = new MapObject;

				int width = m_pMapTileData->getWidth();
				int height = m_pMapTileData->getHeight();
				if (width != 0 || height != 0)
				{
					newObject->initialize(m_pGraphics,
						m_arrObjects.size() + 1,
						m_pMapTileData->getTextureName(),
						m_pMapTileData->getCollisionType(),
						m_pMapTileData->getLayer(),
						iter->getX() + (iter->getWidth() / 2),
						iter->getY() + (iter->getHeight() / 2),
						m_pMapTileData->getWidth(),
						m_pMapTileData->getHeight());
				}
				else
				{
					newObject->initialize(m_pGraphics,
						m_arrObjects.size() + 1,
						m_pMapTileData->getTextureName(),
						m_pMapTileData->getCollisionType(),
						m_pMapTileData->getLayer(),
						iter->getX() + (iter->getWidth() / 2),
						iter->getY() + (iter->getHeight() / 2));
				}
					
				m_pMapTileData->setSelected(false);
				m_arrObjects.emplace_back(newObject);

				std::string log;
				log = "Object Added On [" + std::to_string(count) + "] Name : " + name;
				m_pLogViewer->addLog(log);
				break;
			}
			count++;
		}
	}
	else
	{
		MapObject* newObject = new MapObject;
		int width = m_pMapTileData->getWidth();
		int height = m_pMapTileData->getHeight();
		if (width != 0 || height != 0)
		{
			newObject->initialize(m_pGraphics,
				m_arrObjects.size() + 1,
				m_pMapTileData->getTextureName(),
				m_pMapTileData->getCollisionType(),
				m_pMapTileData->getLayer(),
				m_pMapTileData->getPosition().x,
				m_pMapTileData->getPosition().y,
				m_pMapTileData->getWidth(),
				m_pMapTileData->getHeight());
		}
		else
		{
			newObject->initialize(m_pGraphics,
				m_arrObjects.size() + 1,
				m_pMapTileData->getTextureName(),
				m_pMapTileData->getCollisionType(),
				m_pMapTileData->getLayer(),
				m_pMapTileData->getPosition().x,
				m_pMapTileData->getPosition().y);
		}

	
		m_pMapTileData->setSelected(false);
		m_arrObjects.emplace_back(newObject);

		std::string log;
		log = "Object Added [Free Position : X = " + std::to_string(m_pMapTileData->getPosition().x) + " Y = " 
			+ std::to_string(m_pMapTileData->getPosition().y) + "]" + " Name : " + m_pMapTileData->getTextureName();
		m_pLogViewer->addLog(log);
	}

}


MapTile * MapSystem::getTile(int number)
{
	if (m_arrTiles[number] != nullptr)
		return m_arrTiles[number];
	else
		return nullptr;
}

void MapSystem::setMemoryLinkCameraSystem(CameraSystem * pCameraSystem)
{
	m_pCameraSystem = pCameraSystem;
	m_pMapDataParser->setMemoryLinkCameraSystem(pCameraSystem);
}

void MapSystem::saveData()
{
	m_pMapDataParser->setMapTiles(m_arrTiles);
	m_pMapDataParser->setMapObjects(m_arrObjects);
	m_pMapDataParser->setMapEventObject(m_arrEventObjects);
	m_pMapDataParser->saveData();
}

void MapSystem::loadData()
{
	m_pMapDataParser->loadData();
}
