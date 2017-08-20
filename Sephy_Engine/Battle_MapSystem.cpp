#include "stdafx.h"
#include "Battle_MapSystem.h"


CBattle_MapSystem::CBattle_MapSystem()
{
	m_pGame = nullptr;
	m_pBattleMapDataParser = nullptr;
	m_fMapTotalWidth	= 0.f;
	m_fMapTotalHeight	= 0.f;
	m_fMapCellWidth		= 0.f;
	m_fMapCellHeight	= 0.f;
}


CBattle_MapSystem::~CBattle_MapSystem()
{
	//=======================================
	// Original Object Datas SAFE DELETE
	//  + [Cell / Object / Event Object]
	//=======================================
	for (auto iter : m_vCells)
	{
		SAFE_DELETE(iter);
	}
	m_vCells.clear();

	for (auto iter : m_vObjects)
	{
		SAFE_DELETE(iter);
	}
	m_vObjects.clear();

	for (auto iter : m_vEventObjects)
	{
		SAFE_DELETE(iter);
	}
	m_vEventObjects.clear();


	//=======================================
	// Event Area SAFE DELETE
	//=======================================
	for (auto iter : m_vCollisionArea)
	{
		SAFE_DELETE(iter);
	}
	m_vCollisionArea.clear();

	for (auto iter : m_vStartingArea)
	{
		SAFE_DELETE(iter);
	}
	m_vStartingArea.clear();

	for (auto iter : m_vRespawnArea)
	{
		SAFE_DELETE(iter);
	}
	m_vRespawnArea.clear();

	for (auto iter : m_vRepairArea)
	{
		SAFE_DELETE(iter);
	}
	m_vRepairArea.clear();

	for (auto iter : m_vObserverArea)
	{
		SAFE_DELETE(iter);
	}
	m_vObserverArea.clear();

	SAFE_DELETE(m_pBattleMapDataParser);
}

bool CBattle_MapSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{	
		m_pGame = gamePtr;
		m_pInput = gamePtr->getInput();
		m_pGraphics = gamePtr->getGraphics();

		m_pBattleMapDataParser = new CBattle_MapParser;
		m_pBattleMapDataParser->setMemoryLinkBattleMapSystem(this);
		m_pBattleMapDataParser->setGraphics(m_pGraphics);
		
		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_MapSystem::update(float frameTime)
{
	// Update All Tiles
	for (auto iter : m_vCells)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All Objects
	for (auto iter : m_vObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All EventObject
	for (auto iter : m_vEventObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All Starting Area Flag UI
	for (auto iter : m_vStartingArea)
	{
		iter->update(frameTime);
	}
	// Update All Repair Area
	for (auto iter : m_vRepairArea)
	{
		iter->update(frameTime);
	}
	// Update All Observer Area
	for (auto iter : m_vObserverArea)
	{
		iter->update(frameTime);
	}
	// Update All Weather - Fog Area
	for (auto iter : m_vWeatherFogArea)
	{
		iter->update(frameTime);
	}
}

void CBattle_MapSystem::render()
{
	m_pGraphics->spriteBegin();

	// Draw All Tiles
	for (auto iter : m_vCells)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}

	// Draw All Objects
	for (auto iter : m_vObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}

	// Draw All Event Objects
	for (auto iter : m_vEventObjects)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}
	m_pGraphics->spriteEnd();

	// Render CollsionArea (if DebugMode On -> draw Box)
	for (auto iter : m_vCollisionArea)
	{
		iter->render();
	}

	// Render Starting Area Flag
	for (auto iter : m_vStartingArea)
	{
		iter->render();
	}
	// Render Respawn Area Flag
	for (auto iter : m_vRespawnArea)
	{
		iter->render();
	}
	// Render Repair Area
	for (auto iter : m_vRepairArea)
	{
		iter->render();
	}
	// Render Observer Area
	for (auto iter : m_vObserverArea)
	{
		iter->render();
	}
	// Render Weather - Fog Area
	for (auto iter : m_vWeatherFogArea)
	{
		iter->render();
	}
}

void CBattle_MapSystem::moveX(int distance)
{
	for (auto iter : m_vCells)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}

	for (auto iter : m_vObjects)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}
	for (auto iter : m_vEventObjects)
	{
		iter->moveX(distance);
		iter->moveRectWidth(distance);
	}


	for (auto iter : m_vCollisionArea)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vStartingArea)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vRespawnArea)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vRepairArea)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vObserverArea)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vWeatherFogArea)
	{
		iter->moveX(distance);
	}
}

void CBattle_MapSystem::moveY(int distance)
{
	for (auto iter : m_vCells)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}

	for (auto iter : m_vObjects)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}
	for (auto iter : m_vEventObjects)
	{
		iter->moveY(distance);
		iter->moveRectHeight(distance);
	}

	for (auto iter : m_vCollisionArea)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vStartingArea)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vRespawnArea)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vRepairArea)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vObserverArea)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vWeatherFogArea)
	{
		iter->moveY(distance);
	}
}

bool CBattle_MapSystem::loadBattleMap(std::string mapName)
{
	return m_pBattleMapDataParser->loadBattleMapData(mapName);
}

void CBattle_MapSystem::setupEventObject()
{
	for (auto iter : m_vEventObjects)
	{
		auto enType = iter->getEventObjectType();
		switch (enType)
		{
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX:
			{
				CBattle_MapEventArea_CollisionArea* tempColBox = new CBattle_MapEventArea_CollisionArea;
				tempColBox->initialize(m_pGame);
				tempColBox->setCollisionX(iter->getPosX());
				tempColBox->setCollisionY(iter->getPosY());
				tempColBox->setCollisionWidth(iter->getWidth());
				tempColBox->setCollisionHeight(iter->getHeight());
				m_vCollisionArea.emplace_back(tempColBox);
				break;
			}
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR:
			{
				CBattle_MapEventArea_RepairArea* repairArea = new CBattle_MapEventArea_RepairArea;
				repairArea->initialize(m_pGraphics, iter->getCenterPosX(), iter->getCenterPosY());
				m_vRepairArea.emplace_back(repairArea);
				break;
			}
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER:
			{
				CBattle_MapEventArea_ObserverArea* observerArea = new CBattle_MapEventArea_ObserverArea;
				observerArea->initialize(m_pGraphics, iter->getCenterPosX(), iter->getCenterPosY());
				m_vObserverArea.emplace_back(observerArea);
			}
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG:
			{
				CBattle_MapEventArea_WeatherFogArea* weatherFogArea = new CBattle_MapEventArea_WeatherFogArea;
				weatherFogArea->initialize(m_pGraphics, iter->getCenterPosX(), iter->getCenterPosY());
				m_vWeatherFogArea.emplace_back(weatherFogArea);
				break;
			}
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN:
			{
				CBattle_MapEventArea_RespawnArea* tempArea = new CBattle_MapEventArea_RespawnArea;
				tempArea->initialize(m_pGraphics);
				tempArea->setRespawnAreaCenterX(iter->getCenterPosX());
				tempArea->setRespawnAreaCenterY(iter->getCenterPosY());
				tempArea->setRespawnAreaRadius(battleMapUIRespawnAreaNS::RESPAWN_AREA_DEFAULT_RADIUS);
				m_vRespawnArea.emplace_back(tempArea);
				break;
			}
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING:
			{
				CBattle_MapEventArea_StartingArea* tempFlag = new CBattle_MapEventArea_StartingArea;
				if (m_vStartingArea.size() > 0)
				{
					// Enemy Area
					tempFlag->initialize(m_pGraphics, 1);
					tempFlag->setFlagCenterX(iter->getCenterPosX());
					tempFlag->setFlagCenterY(iter->getCenterPosY());
					tempFlag->setPlayerArea(false);
				}
				else
				{
					// Player Area Setup
					tempFlag->initialize(m_pGraphics, 0);
					tempFlag->setFlagCenterX(iter->getCenterPosX());
					tempFlag->setFlagCenterY(iter->getCenterPosY());
					tempFlag->setPlayerArea(true);
				}

				m_vStartingArea.emplace_back(tempFlag);
				break;
			}
		}
	}
}

float CBattle_MapSystem::getMapBorderLeft() const
{
	return m_vCells[0]->getX();
}

float CBattle_MapSystem::getMapBorderRight() const
{
	auto totalSize = m_vCells.size();
	return m_vCells[totalSize - 1]->getX() + m_vCells[totalSize - 1]->getWidth();
}

float CBattle_MapSystem::getMapBorderTop() const
{	
	return m_vCells[0]->getY();
}

float CBattle_MapSystem::getMapBorderBottom() const
{
	auto totalSize = m_vCells.size();
	return m_vCells[totalSize - 1]->getY() + m_vCells[totalSize - 1]->getHeight();
}
