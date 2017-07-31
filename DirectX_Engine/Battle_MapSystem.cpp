#include "stdafx.h"
#include "Battle_MapSystem.h"


CBattle_MapSystem::CBattle_MapSystem()
{
	m_pBattleMapDataParser = nullptr;
	m_fMapTotalWidth	= 0.f;
	m_fMapTotalHeight	= 0.f;
	m_fMapCellWidth		= 0.f;
	m_fMapCellHeight	= 0.f;
}


CBattle_MapSystem::~CBattle_MapSystem()
{
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

	for (auto iter : m_vStartingAreaFlag)
	{
		SAFE_DELETE(iter);
	}
	m_vStartingAreaFlag.clear();

	SAFE_DELETE(m_pBattleMapDataParser);
}

bool CBattle_MapSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{	
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
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All Objects
	for (auto iter : m_vObjects)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All EventObject
	for (auto iter : m_vEventObjects)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->update(frameTime);
	}

	// Update All Starting Area Flag UI
	for (auto iter : m_vStartingAreaFlag)
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
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}

	// Draw All Objects
	for (auto iter : m_vObjects)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}

	// Draw All Event Objects
	for (auto iter : m_vEventObjects)
	{
		if (MyUtil::getScreenIn(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;

		iter->render();
	}
	m_pGraphics->spriteEnd();

	// Render Starting Area Flag
	for (auto iter : m_vStartingAreaFlag)
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
	for (auto iter : m_vStartingAreaFlag)
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
	for (auto iter : m_vStartingAreaFlag)
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
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN:
			break;
		case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING:
			CBattle_MapUI_StartingArea* tempFlag = new CBattle_MapUI_StartingArea;
			if (m_vStartingAreaFlag.size() > 0)
			{
				// Size > 0? Enemy Area : Player Area 
				tempFlag->initialize(m_pGraphics, 1);
				tempFlag->setFlagCenterX(iter->getCenterPosX());
				tempFlag->setFlagCenterY(iter->getCenterPosY());
			}
			else
			{
				// 	Player Area Setup
				tempFlag->initialize(m_pGraphics, 0);
				tempFlag->setFlagCenterX(iter->getCenterPosX());
				tempFlag->setFlagCenterY(iter->getCenterPosY());
			}

			m_vStartingAreaFlag.emplace_back(tempFlag);
			break;
		}
	}
}
