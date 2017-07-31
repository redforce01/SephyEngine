#include "stdafx.h"
#include "Battle_MainSystem.h"


CBattle_MainSystem::CBattle_MainSystem()
{
	m_pBattle_DataParser = nullptr;
	m_pBattle_CameraSystem = nullptr;
	m_pBattle_MapSystem = nullptr;
	m_pBattle_UnitSystem = nullptr;
}


CBattle_MainSystem::~CBattle_MainSystem()
{
	SAFE_DELETE(m_pBattle_DataParser);
	SAFE_DELETE(m_pBattle_CameraSystem);
	SAFE_DELETE(m_pBattle_MapSystem);
	SAFE_DELETE(m_pBattle_UnitSystem);
}

bool CBattle_MainSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		//=====================================================================
		// Battle Map DataParser - Start
		m_pBattle_DataParser = new CBattle_DataParser;
		m_pBattle_DataParser->loadBattleData();
		// End - Battle Map DataParser
		//=====================================================================
		// Battle Map DataParser - Start
		m_pBattle_CameraSystem = new CBattle_CameraSystem;
		success = m_pBattle_CameraSystem->initialize(gamePtr);
		m_pBattle_MapSystem = new CBattle_MapSystem;
		success = m_pBattle_MapSystem->initialize(gamePtr);
		m_pBattle_UnitSystem = new CBattle_UnitSystem;
		success = m_pBattle_UnitSystem->initialize(gamePtr);
		// End - Battle Map DataParser
		//=====================================================================
		// Each System Connect to The Other Systems - Start
		m_pBattle_MapSystem->setMemoryLinkBattleCameraSystem(m_pBattle_CameraSystem);
		m_pBattle_CameraSystem->setMemoryLinkBattleMapSystem(m_pBattle_MapSystem);
		m_pBattle_CameraSystem->setMemoryLinkBattleUnitSystem(m_pBattle_UnitSystem);
		m_pBattle_UnitSystem->setMemoryLinkBattleCameraSystem(m_pBattle_CameraSystem);
		m_pBattle_UnitSystem->setMemoryLinkBattleMapSystem(m_pBattle_MapSystem);
		// End - Each System Connect to Other Systems
		//=====================================================================
		// Load Battle Data - Start
		//  + Battle Map FileName
		//  + Battle Player Ship List Data
		//  + Battle AI Ship List Data
		auto battleMapName = m_pBattle_DataParser->getBattleMapName();
		m_pBattle_MapSystem->loadBattleMap(battleMapName);
		m_pBattle_MapSystem->setupEventObject();
		
		auto battlePlayerShipData = m_pBattle_DataParser->getBattlePlayerShipData();
		m_pBattle_UnitSystem->loadPlayerShipData(battlePlayerShipData);
		auto battleAIDataShipData = m_pBattle_DataParser->getBattleAIShipData();
		m_pBattle_UnitSystem->loadAIShipData(battleAIDataShipData);
		// End - Load Battle Data
		//=====================================================================
		// Set Camera Min/Max Position - Start
		float totalMapWidth = m_pBattle_MapSystem->getMapTotalWidth();
		float totalMapHeight = m_pBattle_MapSystem->getMapTotalHeight();
		float cellWidth = m_pBattle_MapSystem->getCellWidth();
		float cellHeight = m_pBattle_MapSystem->getCellHeight();

		float resultMaxWidth = totalMapWidth - g_fScreenWidth - cellWidth;
		float resultMaxHeight = totalMapHeight - g_fScreenHeight - cellHeight;
		m_pBattle_CameraSystem->getBattleMinimapViewer()->setMapWidth(totalMapWidth);
		m_pBattle_CameraSystem->getBattleMinimapViewer()->setMapHeight(totalMapHeight);
		m_pBattle_CameraSystem->getBattleMinimapViewer()->setUpCam();
		m_pBattle_CameraSystem->setCameraMinPos(0 + cellWidth, 0 + cellHeight);
		m_pBattle_CameraSystem->setCameraMaxPos(
			totalMapWidth - g_fScreenWidth - cellWidth,
			totalMapHeight - g_fScreenHeight - cellHeight * 1.5f);
		m_pBattle_CameraSystem->setCameraPos(cellWidth, cellHeight);
		// End - Set Camera Min/Max Position
		//=====================================================================
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMainSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_MainSystem::update(float frameTime)
{
	m_pBattle_CameraSystem->update(frameTime);
	m_pBattle_MapSystem->update(frameTime);
	m_pBattle_UnitSystem->update(frameTime);
}

void CBattle_MainSystem::render()
{
	m_pBattle_MapSystem->render();
	m_pBattle_UnitSystem->render();
	m_pBattle_CameraSystem->render();
}

void CBattle_MainSystem::ai()
{
	m_pBattle_UnitSystem->ai();
}

void CBattle_MainSystem::collision()
{
	m_pBattle_UnitSystem->collision();
}
